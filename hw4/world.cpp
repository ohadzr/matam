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

/**************************************
 *        Interface Functions         *
 **************************************/

World::World() : world_map(KGraph<std::string,Location*,DIRECTIONS>(nullptr)) {
}

World::~World() {
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
        return;
    }
    if ( (*Leader).GetTeam() == trainer.GetTeam() ) return;////////////

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

void World::GYM::fightOutcome( Trainer& winner, Trainer& loser ) {
	winner.updateLevel(winner.GetLevel() + (int)ceil((loser.GetLevel())/2));//TODO: what to do with numbers
    winner.updateFightBonus(WINNER_BONUS);
    loser.updateFightBonus(LOSER_BONUS);
	if (Leader->GetName() == loser.GetName()) {
		Leader->updateFightBonus(-LEADER_BONUS);
		winner.updateFightBonus(LEADER_BONUS);
	}
//    updateBonusPoints(winner, WINNER_BONUS);
//    updateBonusPoints(loser, LOSER_BONUS);
}

//void World::GYM::updateBonusPoints(Trainer &trainer, int bonus){
//	Team trainer_team = trainer.GetTeam();
//	switch (trainer_team) {
//	case YELLOW : team_bonus_yellow += bonus ; break;
//	case RED : team_bonus_red += bonus ; break;
//	case BLUE : team_bonus_blue += bonus ; break;
//	}
//}

//true if second win
bool World::GYM::makeFight( Trainer& first , Trainer& second ) {
	Pokemon first_strongest = first.GetStrongestPokemon();
	Pokemon second_strongest = second.GetStrongestPokemon();

	bool first_died = second_strongest.Hit( first_strongest );
	bool second_died = first_strongest.Hit( second_strongest );

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
		else first_strongest.Train( 1 + (first_strongest.Level())/10 ); //TODO: how to MACRO this?
	}
	if ( second_item ) {
		if ( second_item->getType() == "POTION" ) second_strongest.Heal();
		else second_strongest.Train( 1 + (second_strongest.Level())/10 );
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
	if ( (int) trainers_.size() == LAST_TRAINER_IN_GYM ) {
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

	if ( one_team_left_substitute ) return one_team_left_substitute;

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
    for( std::vector<Trainer*>::iterator it = trainers_.begin(); it !=
    		trainers_.end(); ++it ) {
        if ( (*it)->GetTeam() == team) {
            if (candidate == nullptr)
                candidate = *it;
            else if ((**it) > (*candidate))
                candidate = *it;
        }
    }

  return candidate;
}

//TODO: Pokestop

World::Pokestop::Pokestop(std::vector<std::string> input_vector) :
		item_vector(std::vector<Item*>()) {
	if (input_vector.size() % 2 != 0) //Check if args right amount of args
		throw WorldInvalidInputLineException();

	while (input_vector.size() != 0) {
		std::string item_type = input_vector[ITEM_TYPE];
		int item_level = atoi(input_vector[ITEM_LEVEL].c_str());
		input_vector.erase(input_vector.begin());
		input_vector.erase(input_vector.begin());

		try {
			Item new_item = Item(item_type, item_level);
			item_vector.push_back(&new_item);
		}
		catch (ItemInvalidArgsException& e) {
			throw WorldInvalidInputLineException();
		}

	}

}

World::Pokestop::~Pokestop() {
}

void World::Pokestop::Arrive(Trainer &trainer) {
    Location::Arrive( trainer );

    for (std::vector<Item*>::iterator it = item_vector.begin() ;
         it != item_vector.end(); ++it) {
        if ((*it)->getLevel() <= trainer.GetLevel()){
            trainer.addItem(**it);
            item_vector.erase(it); //TODO: PROBLEM?? does this delete trainer's item?
            break;
        }
    }
}


//TODO: Starbucks

World::Starbucks::Starbucks(std::vector<std::string> input_vector) :
		pokemon_vector(std::vector<Pokemon*>()){

	if (input_vector.size() % 3 != 0) //Check if args right amount of args
		throw WorldInvalidInputLineException();

	while (input_vector.size() != 0) {
		std::string pokemon_name = input_vector[POKEMON_NAME];
		double pokemon_cp = atof(input_vector[POKEMON_CP].c_str());
		int pokemon_level = atoi(input_vector[POKEMON_LEVEL].c_str());
		input_vector.erase(input_vector.begin());
		input_vector.erase(input_vector.begin());
		input_vector.erase(input_vector.begin());

		try{
			Pokemon new_pokemon = Pokemon(pokemon_name,
										  pokemon_cp, pokemon_level);
			pokemon_vector.push_back(&new_pokemon);
		}
		catch (PokemonInvalidArgsException& e) {
			throw WorldInvalidInputLineException();
		}
	}
}

World::Starbucks::~Starbucks() {}

void World::Starbucks::Arrive(Trainer &trainer) {
    Location::Arrive( trainer );

    std::vector<Pokemon*>::iterator it = pokemon_vector.begin();
    if (trainer.TryToCatch(**it)) {
        pokemon_vector.erase(it); //TODO: PROBLEM?? - check if this delete the pokemon the trainer caught - maybe send a copy of the pokemon (above)?
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

	World::createLocationByType(location_name, location_type,
								input_vector, world);

	world.location_names.insert(location_name);
	return input;
}

std::vector<std::string> World::parseInput(std::istream &input) {
	std::vector<std::string> input_vector = std::vector<std::string>();
	std::string input_string;
	input >> input_string;
	std::string delimiter = " ";

	size_t pos = 0;
	std::string token;
	while ((pos = input_string.find(delimiter)) != std::string::npos) {
		token = input_string.substr(0, pos);
		input_vector.push_back(std::string(token));
		input_string.erase(0, pos + delimiter.length());
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
		World::GYM new_gym = World::GYM();
		world.world_map.Insert(location_name, &new_gym);
	}
	else if (location_type == "POKESTOP") {
		World::Pokestop new_pokestop = World::Pokestop(input_vector);
		world.world_map.Insert(location_name, &new_pokestop);
	}
	else {
		World::Starbucks new_starbucks = World::Starbucks(input_vector);
		world.world_map.Insert(location_name, &new_starbucks);
	}
}


void World::Connect(std::string const &key_u, std::string const &key_v, int i_u,
					int i_v) {
	world_map.Connect(key_u, key_v, i_u, i_v);
}