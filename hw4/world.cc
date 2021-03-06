/**************************************
 *       Header files include         *
 **************************************/

#include "world.h"

/**************************************
 *               Using                *
 **************************************/

using mtm::pokemongo::World;
using mtm::pokemongo::Location;
using mtm::pokemongo::Team;
using mtm::pokemongo::PokemonType;
using std::set;

const string World::STRING_TO_INT = "0123456789";
const string World::STRING_TO_DOUBLE = "0123456789.";


/**************************************
 *        Interface Functions         *
 **************************************/

World::World() : KGraph(KGraph<std::string, Location*, DIRECTIONS>(nullptr)),
				 location_names(std::set<string>()) {
}

World::~World() {
	std::set<string>::iterator it = location_names.begin();
	for (; it != location_names.end() ; it ++) {
		Location* location = this->operator[](*it);
		std::vector<Trainer*> trainers = location->GetTrainers();
		std::vector<Trainer*>::const_iterator t_it = trainers.begin();
		for (; t_it != trainers.end(); t_it++){
			delete *t_it;
		}
		delete location;
	}
}

World::GYM::GYM() : Leader(nullptr) {
}

World::GYM::~GYM() {
}

void World::GYM::switchLeader( Trainer& leader) {
    Leader = &leader;
}

void World::GYM::Arrive(Trainer& trainer) {
	Location::Arrive( trainer );

    if ( Leader == nullptr ) {
        GYM::switchLeader( trainer );
		trainer.updateFightBonus(LEADER_BONUS);
        return;
    }
    if ( (*Leader).GetTeam() == trainer.GetTeam() ) return;

    if ( !Fight( *Leader , trainer ) ) return;

    switchLeader( trainer );
}

bool World::GYM::Fight( Trainer& first , Trainer& second ) {
    try {
        Pokemon first_strongest = first.GetStrongestPokemon();
        try {
            Pokemon second_strongest = second.GetStrongestPokemon();
            prepareToBattle( first , second);
			return makeFight( first , second );
        }
        catch (TrainerNoPokemonsFoundException& e) {
        	fightOutcome( first , second );
        	return false;
        }
    }
    catch (TrainerNoPokemonsFoundException& e) {
        try {
        	Pokemon second_strongest = second.GetStrongestPokemon();
        	fightOutcome( second , first );
        	return true;
        }
        catch (TrainerNoPokemonsFoundException& e) {
            return compareByTeam( first , second );
        }
    }
}

int World::GYM::winnerNewLevel(int winner_old_level, int loser_old_level) {
	return winner_old_level +(int)ceil(((double)loser_old_level)/2);
}

double World::GYM::pokemonBoost(int pokmon_old_level ) {
	return ((double)(pokmon_old_level)/10) ;
}

void World::GYM::fightOutcome( Trainer& winner, Trainer& loser ) {
	int new_level = winnerNewLevel(winner.GetLevel(), loser.GetLevel());
	winner.updateLevel(new_level);
	winner.updateFightBonus(WINNER_BONUS);
	loser.updateFightBonus(LOSER_BONUS);
	if (Leader->GetName() == loser.GetName()) {
		Leader->updateFightBonus(-LEADER_BONUS);
		winner.updateFightBonus(LEADER_BONUS);
	}
}

//true if second win
bool World::GYM::makeFight( Trainer& first , Trainer& second ) {
	Pokemon first_strongest = first.GetStrongestPokemon();
	Pokemon second_strongest = second.GetStrongestPokemon();

	bool first_died = (second.GetStrongestPokemon()).Hit(
			first.GetStrongestPokemon());
	bool second_died = (first.GetStrongestPokemon()).Hit(
			second.GetStrongestPokemon());

    if ( first_strongest == second_strongest){
    	updateDeathResult( first , second , first_died, second_died );
    	return compareByTeam( first , second );
    }

    if ( first_strongest < second_strongest ) {
    	updateDeathResult( first , second , first_died, second_died );
    	fightOutcome( second , first );
        return true;
    }

    updateDeathResult( first , second , first_died, second_died );
    fightOutcome( first , second );
    return false;

}

//true if second bigger
bool World::GYM::compareByTeam( Trainer& first , Trainer& second ) {
	Team first_team = first.GetTeam();
	Team second_team = second.GetTeam();

	if ( (first_team == BLUE) && (second_team == YELLOW) ) return true;
	if ( (first_team == YELLOW) && (second_team == RED) ) return true;
    return (first_team == RED) && (second_team == BLUE) ;
}

void World::GYM::prepareToBattle( Trainer& first , Trainer& second ) {
	Pokemon first_strongest = first.GetStrongestPokemon();
	Pokemon second_strongest = second.GetStrongestPokemon();

	Item* first_item = first.getOldestItem() ;
    Item* second_item = second.getOldestItem() ;

	if ( first_item ) {
		if ( first_item->getType() == "POTION" ) first_strongest.Heal();
		else first_strongest.Train( pokemonBoost(first_strongest.Level()) );
		delete first_item;
	}
	if ( second_item ) {
		if ( second_item->getType() == "POTION" ) second_strongest.Heal();
		else second_strongest.Train( pokemonBoost(second_strongest.Level()) );
		delete first_item;
	}
}

void World::GYM::updateDeathResult(Trainer& first , Trainer& second , bool first_died,
						    bool second_died ) {
	if ( first_died ) first.KillStrongestPokemon();
	if ( second_died ) second.KillStrongestPokemon();
}

void World::GYM::Leave(Trainer &trainer) {
	if ( &trainer != Leader ) {
		Location::Leave( trainer );
		return;
	}
	if ( (int) GetTrainers().size() == LAST_TRAINER_IN_GYM ) {
		Location::Leave( trainer );
		trainer.updateFightBonus(-LEADER_BONUS);
		Leader = nullptr;
		return;
	}
	Leader = this->findNextLeader();
	Leader->updateFightBonus(LEADER_BONUS);
	Location::Leave( trainer );

	return;
}

Trainer* World::GYM::findNextLeader() {
	Trainer* red_candidate = candidateForLeadership( RED );
	Trainer* blue_candidate = candidateForLeadership( BLUE );
	Trainer* yellow_candidate = candidateForLeadership( YELLOW );

	Trainer* team_member_susbstitute = checkTeamSubstitute( red_candidate ,
			 blue_candidate , yellow_candidate );
	if ( team_member_susbstitute ) return team_member_susbstitute;

	Trainer* one_team_left_substitute = checkisOneTeamLeft ( red_candidate ,
				 blue_candidate , yellow_candidate );

	if ( one_team_left_substitute  ) return one_team_left_substitute;

	Trainer* best_out_of_two_substitute = checkBestOutOfTwoSubstitute (
			red_candidate , blue_candidate , yellow_candidate );

	return best_out_of_two_substitute;

}

Trainer* World::GYM::checkBestOutOfTwoSubstitute(Trainer* red_candidate ,
		Trainer* blue_candidate , Trainer* yellow_candidate ) {
	if ( red_candidate && blue_candidate ) {
		if ( Fight( *red_candidate , *blue_candidate ) )
			return blue_candidate;
		return red_candidate;
	}
	if ( red_candidate && yellow_candidate ){
		if ( Fight( *red_candidate , *yellow_candidate ) )
			return yellow_candidate;
		return red_candidate;
	}
	if ( blue_candidate && yellow_candidate ) {
		if ( Fight( *blue_candidate , *yellow_candidate ) )
			return yellow_candidate;
		return blue_candidate;
	}
	return nullptr;
}

Trainer* World::GYM::checkTeamSubstitute(Trainer* red_candidate ,
		Trainer* blue_candidate , Trainer* yellow_candidate ) {
	Team home_team = Leader->GetTeam();
	if ( red_candidate ) {
		if ( red_candidate->GetTeam() == home_team ) return red_candidate;
	}
	if ( blue_candidate ) {
		if ( blue_candidate->GetTeam() == home_team ) return blue_candidate;
	}
	if ( yellow_candidate ) {
		if ( yellow_candidate->GetTeam() == home_team ) return yellow_candidate;
	}
	return nullptr;
}

Trainer* World::GYM::checkisOneTeamLeft(Trainer* red_candidate ,
		Trainer* blue_candidate , Trainer* yellow_candidate ) {
	if ( (red_candidate && blue_candidate) ||
		 (red_candidate && yellow_candidate) ||
		 (blue_candidate && yellow_candidate) )
		return nullptr;

	if ( red_candidate ) return red_candidate;
	if ( blue_candidate ) return blue_candidate;
	if ( yellow_candidate ) return yellow_candidate;

	return nullptr;
}



Trainer* World::GYM::candidateForLeadership( Team team ) {
	Trainer* candidate = nullptr;
    for( std::vector<Trainer*>::const_iterator it = GetTrainers().begin(); it !=
    		GetTrainers().end(); ++it ) {
        if ( (*it)->GetTeam() == team) {
            if (candidate == nullptr)
                candidate = *it;
            else if ((**it) > (*candidate))
                candidate = *it;
        }
    }

  return candidate;
}


World::Pokestop::Pokestop(std::vector<std::string>& input_vector) {
	if (input_vector.size() % 2 != 0) //Check if right amount of args
		throw WorldInvalidInputLineException();

	while (input_vector.size() != 0) {
		std::string item_type = input_vector[ITEM_TYPE];
        if (input_vector[ITEM_LEVEL].find_first_not_of(STRING_TO_INT) !=
                string::npos)
            throw WorldInvalidInputLineException();
		int item_level = atoi(input_vector[ITEM_LEVEL].c_str());
		input_vector.erase(input_vector.begin());
		input_vector.erase(input_vector.begin());

		try {
			Item item = Item(item_type, item_level);
			Item new_item = Item(item);
			item_vector.push_back(new_item);
		}
		catch (ItemInvalidArgsException& e) {
			throw WorldInvalidInputLineException();
		}

	}

}

World::Pokestop::~Pokestop() {}

void World::Pokestop::Arrive(Trainer &trainer) {
    Location::Arrive( trainer );

    for (std::vector<Item>::iterator it = item_vector.begin() ;
         it != item_vector.end(); ++it) {
        if ((*it).getLevel() <= trainer.GetLevel()){
            trainer.addItem(&(*it));
            item_vector.erase(it);
            break;
        }
    }
}



World::Starbucks::Starbucks(std::vector<std::string>& input_vector) :
		pokemon_vector(std::vector<Pokemon>()) {
	if (input_vector.size() % 3 != 0) //Check if args right amount of args
		throw WorldInvalidInputLineException();

	while (input_vector.size() != 0) {
		std::string pokemon_name = input_vector[POKEMON_NAME];
        if (input_vector[POKEMON_CP].find_first_not_of(STRING_TO_DOUBLE) !=
                string::npos ||
            input_vector[POKEMON_LEVEL].find_first_not_of(STRING_TO_INT) !=
                string::npos ||
            std::count(input_vector[POKEMON_CP].begin(),
                       input_vector[POKEMON_CP].end(),'.') > 1)
            throw WorldInvalidInputLineException();

		double pokemon_cp = atof(input_vector[POKEMON_CP].c_str());
		int pokemon_level = atoi(input_vector[POKEMON_LEVEL].c_str());
		input_vector.erase(input_vector.begin());
		input_vector.erase(input_vector.begin());
		input_vector.erase(input_vector.begin());

		try{
            Pokemon new_pokemon = Pokemon(pokemon_name, pokemon_cp,
										  pokemon_level);
			pokemon_vector.push_back(new_pokemon);
		}
		catch (PokemonInvalidArgsException& e) {
			throw WorldInvalidInputLineException();
		}
	}
}

World::Starbucks::~Starbucks() {}

void World::Starbucks::Arrive(Trainer &trainer) {
    Location::Arrive( trainer );

	if (pokemon_vector.size() == 0)
		return;
    std::vector<Pokemon>::iterator it = pokemon_vector.begin();
	if (trainer.TryToCatch(*it)) {
		pokemon_vector.erase(it);
    }
}





std::istream& mtm::pokemongo::operator>>(std::istream& input, World& world) {
    // split String Into vector
    std::vector<std::string> input_vector = World::parseInput(input);

    if (input_vector.size() < 2)
        throw WorldInvalidInputLineException();

    std::string location_type = input_vector[World::LOCATION_TYPE];
    std::string location_name = input_vector[World::LOCATION_NAME];
    //remove from list
    input_vector.erase(input_vector.begin());
    input_vector.erase(input_vector.begin());

    // check if first parameter is valid
    if (! (location_type == "GYM" || location_type == "POKESTOP" ||
			location_type == "STARBUCKS") )
        throw WorldInvalidInputLineException();

	// check if second parameter doesn't exist
    if (world.location_names.find(location_name) != world.location_names.end())
		throw WorldLocationNameAlreadyUsed();

	world.createLocationByType(location_name, location_type,
								input_vector, world);

	world.location_names.insert(location_name);
	return input;
}

std::vector<std::string> World::parseInput(std::istream &input) {
	std::vector<std::string> input_vector = std::vector<std::string>();
	std::string input_string;
	while (input >> input_string){
		input_vector.push_back(input_string);
	}

	return input_vector;
}

void World::createLocationByType(std::string &location_name,
								 std::string &location_type,
								 std::vector<std::string> input_vector,
								 World &world) {
	if (location_type == "GYM") {
		if (input_vector.size() != 0)
			throw WorldInvalidInputLineException();
		World::GYM* new_gym = new World::GYM();
		this->Insert(location_name, new_gym);
	}
	else if (location_type == "POKESTOP") {
		World::Pokestop* new_pokestop = new World::Pokestop(input_vector);
		this->Insert(location_name, new_pokestop);
	}
	else {
		World::Starbucks* new_starbucks = new World::Starbucks(input_vector);
		this->Insert(location_name, new_starbucks);
	}
}

void World::Insert(string const& location_name, Location* const& new_location) {
	for (std::set<string>::iterator it = location_names.begin();
			it != location_names.end() ; it ++) {
		if (*it == location_name)
			throw WorldLocationNameAlreadyUsed();
	}
	KGraph::Insert(location_name, new_location);
	location_names.insert(location_name);
}

void World::Remove(string const& location_name) {
	for (std::set<string>::iterator it = location_names.begin();
		 it != location_names.end() ; it ++) {
		if (*it == location_name)
		{
			delete (*this)[location_name];
			KGraph::Remove(location_name);
			location_names.erase(it);
			return;
		}
	}
	throw WorldLocationNotFoundException();
}
