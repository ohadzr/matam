/**************************************
 *       Header files include         *
 **************************************/

#include "world.h"
#include "k_graph_mtm.h"

/**************************************
 *               Using                *
 **************************************/

using mtm::pokemongo;
using mtm::pokemongo::World;
using mtm::pokemongo::World::GYM;
using mtm::pokemongo::Location;
using mtm::pokemongo::Team;

/**************************************
 *        Interface Functions         *
 **************************************/

World::World() :Team_bonus_yellow(0),Team_bonus_red(0),Team_bonus_blue(0),
        world_map(KGraph<std::string,Location*,DIRECTIONS>(nullptr)) {
}

World::~World() {}

World::GYM::GYM():Leader(nullptr){}

World::GYM::~GYM(){}

void World::GYM::switchLeader( Trainer& leader) {
    Leader = &leader;
}

void World::GYM::Arrive(Trainer& trainer) {
	Location::Arrive( trainer );

    if ( Leader == nullptr ) {
        GYM::switchLeader( trainer );
        return;
    }
    if ( (*Leader).GetTeam() == trainer.GetTeam() ) return;

    if ( !Fight( *Leader , trainer ) ) return;

    switchLeader( trainer );
}

bool GYM::Fight( Trainer& first , Trainer& second ) {
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

void GYM::fightOutcome( Trainer& winner, Trainer& loser ) {
	winner.t_level += ceil((loser.t_level)/2);//TODO: what to do with numbers
	upDateBonusPoints( winner , WINNER_BONUS );
	upDateBonusPoints( loser , LOSER_BONUS );
}

void GYM::upDateBonusPoints( Trainer& trainer , int bonus ){
	Team trainer_team = trainer.GetTeam();
	switch (trainer_team) {
	case YELLOW : Team_bonus_yellow += bonus ; break;
	case RED : Team_bonus_red += bonus ; break;
	case BLUE : Team_bonus_blue += bonus ; break;
	}
}

//true if second win
bool GYM::makeFight( Trainer& first , Trainer& second ) {
	Pokemon first_strongest = first.GetStrongestPokemon();
	Pokemon second_strongest = second.GetStrongestPokemon();

	bool first_died = second_strongest.Hit( first_strongest );
	bool second_died = first_strongest.Hit( second_strongest );

    if ( first_strongest == second_strongest){
    	updateDethResult( first , second , first_died, second_died );
    	return compareByTeam( first , second );
    }

    if ( first_strongest < second_strongest ) {
    	updateDethResult( first , second , first_died, second_died );
    	fightOutcome( second , first );
    }
    else {
    	updateDethResult( first , second , first_died, second_died );
    	fightOutcome( first , second );
    }
}

//true if second bigger
bool GYM::compareByTeam( Trainer& first , Trainer& second ) {
	Team first_team = first.GetTeam();
	Team second_team = second.GetTeam();

	if ( (first_team == BLUE) && (second_team == YELLOW) ) return true;
	if ( (first_team == YELLOW) && (second_team == RED) ) return true;
	if ( (first_team == RED) && (second_team == BLUE) ) return true;

	return false;
}

void GYM::prepareToBattle( Trainer& first , Trainer& second ) {
	Pokemon first_strongest = first.GetStrongestPokemon();
	Pokemon second_strongest = second.GetStrongestPokemon();

	Item* first_item = first.itemList.front() ;
	Item* second_item = second.itemList.front() ;

	if ( first_item ) {
		if ( first_item->value == "potion" ) first_strongest.Heal();
		else first_strongest.Train( first_item->value );
	}
	if ( second_item ) {
		if ( second_item->value == "potion" ) second_strongest.Heal();
		else second_strongest.Train( second_item->value );
	}
}

void GYM::updateDethResult(Trainer& first , Trainer& second , bool first_died,
						    bool second_died ) {
	if ( first_died ) first.KillStrongestPokemon();
	if ( second_died ) second.KillStrongestPokemon();
}

void World::GYM::Leave(Trainer &trainer) {
	if ( &trainer != Leader ) {
		Location::Leave( trainer );
		return;
	}
	if ( trainers_.size() == LAST_TRAINER_IN_GYM ) {
		Location::Leave( trainer );
		Leader = nullptr;
		return;
	}
	Leader = this->findNextLeader();
	Location::Leave( trainer );

	return;
}

Trainer* GYM::findNextLeader() {
	Trainer* red_candidate = candidateForLeadership( RED );
	Trainer* blue_candidate = candidateForLeadership( BLUE );
	Trainer* yellow_candidate = candidateForLeadership( YELLOW );

	Trainer* team_member_usbstitute = checkTeamSubstitute( red_candidate ,
			 blue_candidate , yellow_candidate );
	if ( team_member_usbstitute ) return team_member_usbstitute;

	Trainer* one_team_left_substitute = checkisOneTeamLeft ( red_candidate ,
				 blue_candidate , yellow_candidate );

	if ( one_team_left_substitute ) return one_team_left_substitute;

	Trainer* best_out_of_two_substitute = checkBestOutOfTwoSubstitute (
			red_candidate , blue_candidate , yellow_candidate );

	return best_out_of_two_substitute;

}

Trainer* GYM::checkBestOutOfTwoSubstitute(Trainer* red_candidate ,
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

Trainer* GYM::checkTeamSubstitute(Trainer* red_candidate ,
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

Trainer* GYM::checkisOneTeamLeft(Trainer* red_candidate ,
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



Trainer* GYM::candidateForLeadership( Team team ) {
	Trainer* candidate = nullptr;
    for( std::vector<Trainer*>::iterator it = trainers_.begin(); it !=
    		trainers_.end(); ++it ) {
        if ( (*it)->GetTeam() == team ) {
        	candidate = it;
        	break;
        }
    }

    for( std::vector<Trainer*>::iterator it = trainers_.begin(); it !=
    		trainers_.end(); ++it ) {
        if ( ((*it)->GetTeam() == team ) && ( (*it) > (*candidate) ) ) {
        	candidate = it;
        	break;
        }
    }

  return candidate;
}

std::string GYM::GYMgetTeam() {
	if ( !Leader ) return nullptr;
	return Leader->teamToString();
}

//TODO: Pokestop

World::Pokestop::Pokestop() : item_vector(std::vector<const Item*>()) {
}

World::Pokestop::~Pokestop() {
}

void World::Pokestop::addItem(const Item& item) {
    item_vector.push_back(&item);
}

void World::Pokestop::Arrive(Trainer &trainer) {
    for (std::vector<const Item*>::const_iterator it = item_vector.begin() ;
         it != item_vector.end(); ++it) {
        if ((**it).getLevel() <= trainer.GetLevel()){
            trainer.addItem(**it);
            item_vector.erase(it); //TODO: PROBLEM?? does this delete trainer's item?
            break;
        }
    }
}

World::Pokestop::Item::Item(const std::string &type, const int level) :
        type(string(type)), level(level){
}

World::Pokestop::Item::~Item() {}

const World::Pokestop::Item::Item(const Item &item) :
        type(string(item.type)), level(item.level){
}

const std::string World::Pokestop::Item::getType(const Item &item) {
    return item.type;
}

const int World::Pokestop::Item::getLevel(const Item &item) {
    return item.level;
}



//TODO: Starbucks

World::Starbucks::Starbucks() : pokemon_vector(std::vector<Pokemon*>()){}

World::Starbucks::~Starbucks() {}

void World::Starbucks::Arrive(Trainer &trainer) {
    std::vector<Pokemon*>::iterator it = pokemon_vector.begin();
    if (trainer.TryToCatch(**it)) {
        pokemon_vector.erase(it); //TODO: PROBLEM?? - check if this delete the pokemon the trainer caught - maybe send a copy of the pokemon (above)?
    }
}



std::istream& mtm::pokemongo::operator>>(std::istream& input, World& world) { //TODO: continue here
    // split String Into vector
    // check first parameter - is valid
    // check second parameter - doesn't exist
    // send to create by first parameter
    // add created location to world [and save it name in the key vector???]
}
