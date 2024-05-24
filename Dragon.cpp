
/*
CSCI235 Spring 2024
Project 4 - MycoMorsels
Georgina Woo
Dec 24 2023
Dragon.cpp implements the constructors and private and public functions of the Dragon class
*/

// Nabil Said
// nabil.said54@myhunter.cuny.edu
// CSCI 235 - Project 1
// Prof: Tiziana Ligorio

#include "Dragon.hpp"
#include "Creature.hpp"

Dragon::Dragon() : element_{NONE}, number_of_heads_{1}, flight_{false}
{
    setCategory(MYSTICAL); 
    
}

Dragon::Dragon(const std::string& name, Category category, int hitpoints, int level, bool tame, Element element, int number_of_heads, bool flight) : Creature(name, category, hitpoints, level, tame)
{
    element_ = element;
    if(!setNumberOfHeads(number_of_heads))
    {
        number_of_heads_ = 1;
    }
    flight_ = flight;
}

std::string Dragon::getElement() const
{
    switch(element_)
    {
        case FIRE:
            return "FIRE";
        case WATER:
            return "WATER";
        case EARTH:
            return "EARTH";
        case AIR:
            return "AIR";
        default:
            return "NONE";
    }
}

void Dragon::setElement(const Element& element)
{
    element_ = element;
}

int Dragon::getNumberOfHeads() const
{
    return number_of_heads_;
}

bool Dragon::setNumberOfHeads(const int& number_of_heads)
{
    if(number_of_heads > 0)
    {
        number_of_heads_ = number_of_heads;
        return true;
    }
    else
    {
        return false;
    }
}

bool Dragon::getFlight() const
{
    return flight_;
}

void Dragon::setFlight(const bool& flight)
{
    flight_ = flight;
}


void Dragon::display() const
{
    std::cout << "DRAGON - " << getName() << std::endl;
    std::cout << "CATEGORY: " << getCategory() << std::endl;
    std::cout << "HP: " << getHitpoints() << std::endl;
    std::cout << "LVL: " << getLevel() << std::endl;
    std::cout << "TAME: " << (isTame() ? "TRUE" : "FALSE") << std::endl;
    std::cout << "ELEMENT: " << getElement() << std::endl;
    std::cout << "HEADS: " << getNumberOfHeads() << std::endl;
    std::cout << "IT " << (getFlight() ? "CAN" : "CANNOT") << " FLY" << std::endl;
}



bool Dragon::eatMycoMorsel()
{
    if(getCategory() == "UNDEAD")
    {
        setTame(true);
        setHitpoints(getHitpoints() + 1);
        return false;
    }
    else if(getCategory() == "ALIEN")
    {
        setHitpoints(getHitpoints() + 1);
        return false;
    }
    else if(getCategory() == "MYSTICAL")
    {
        if(getElement() == "FIRE" || getElement() == "EARTH")
        {
            setHitpoints(getHitpoints() + 1);
            return false;
        }
        else if(getHitpoints() == 1)
        {
            return true;
        }
        else
        {
            setHitpoints(getHitpoints() - 1);
            setTame(false);
            return false;
        }
    }
    else
    {
        return false;
    }
}

/**
 * @param: A const reference to int corresponding to the attack to be added to the attack queue.
 * @post: Adds an attack to the attack queue based on the int parameter.
 * Here are the attacks for the Dragon:

* 1: Attack name: BITE
*      if ALIEN: 4 PHYSICAL
*      if MYSTICAL: 2 PHYSICAL, and additional damage of 1 [FIRE/WATER/EARTH/AIR] if the Dragon has an elemental affinity of FIRE, WATER, EARTH, or AIR)
*      if UNDEAD: 2 PHYSICAL, 1 POISON
*      if UNKNOWN: 2 PHYSICAL

* 2: Attack name: STOMP
*      if ALIEN: 2 PHYSICAL
*      if MYSTICAL: 1 PHYSICAL, and additional damage of 1 [FIRE/WATER/EARTH/AIR] if the Dragon has an elemental affinity of FIRE, WATER, EARTH, or AIR)
*      if UNDEAD: 1 PHYSICAL, 1 POISON
*      if UNKNOWN: 1 PHYSICAL

* 3: Attack name: [ELEMENTAL BREATH/BAD BREATH], where the name is ELEMENTAL BREATH if the Dragon has an elemental affinity, otherwise it is BAD BREATH
*      if ALIEN: 6 [POISON/FIRE/WATER/EARTH/AIR], where the damage type is the Dragon's elemental affinity if it has one, otherwise it is POISON
*      if MYSTICAL: 3 [POISON/FIRE/WATER/EARTH/AIR], where the damage type is the Dragon's elemental affinity if it has one, otherwise it is POISON
*      if UNDEAD: 3 [POISON/FIRE/WATER/EARTH/AIR], 1 POISON. The damage types and amount are added to the vector as two separate entries, even if both entries are POISON type.
*      if UNKNOWN: 3 [POISON/FIRE/WATER/EARTH/AIR] where the damage type is the Dragon's elemental affinity if it has one, otherwise it is POISON
*/

void Dragon::addAttack(const int &attack)
{
    Attack attack_; // creating a Attack obj
    std::vector<std::string> type ={}; // creating type vector
    std::vector<int> damage ={}; // creating damage vector

    if (attack ==1){

        attack_.name_= "BITE"; // updating name

        if (getCategory()=="ALIEN"){

            type.push_back("PHYSICAL"); // updating type

            damage.push_back(4);// updating damage
        }
        else if (getCategory()=="MYSTICAL"){

            type.push_back("PHYSICAL"); // updating type
            damage.push_back(2); // updating damage

            if (getElement()=="FIRE"||getElement()=="WATER"||getElement()=="EARTH"||getElement()=="AIR"){
                damage.push_back(1);
                type.push_back(getElement());
            }
            
        }
        else if (getCategory()=="UNDEAD"){

            type.push_back("PHYSICAL"); // updating type
            type.push_back("POISON"); // updating type

            damage.push_back(2); // updating damage
            damage.push_back(1);

        } 
        else if (getCategory()=="UNKNOWN"){

            type.push_back("PHYSICAL"); // updating type

            damage.push_back(2); // updating damage
        }
    }

    else if (attack ==2){

        attack_.name_= "STOMP"; // updating name

        if (getCategory()=="ALIEN"){

            type.push_back("PHYSICAL"); // updating type

            damage.push_back(2); // updating damage
        }
        else if (getCategory()=="MYSTICAL"){

            type.push_back("PHYSICAL"); // updating type
            damage.push_back(1); // updating damage

            if (getElement()=="FIRE"||getElement()=="WATER"||getElement()=="EARTH"||getElement()=="AIR"){
                damage.push_back(1);
                type.push_back(getElement());
            }
        }
        else if (getCategory()=="UNDEAD"){
            
            type.push_back("PHYSICAL"); // updating type
            type.push_back("POISON"); // updating type

            damage.push_back(1); // updating damage
            damage.push_back(1); // updating damage
        } 
        else if (getCategory()=="UNKNOWN"){

            type.push_back("PHYSICAL"); // updating type

            damage.push_back(1); // updating damage
        }
    }

    else if (attack ==3){

        if(getElement()!="NONE"){attack_.name_= "ELEMENTAL BREATH";}// updating name
        else{attack_.name_= "BAD BREATH";} 

        if (getCategory()=="ALIEN"){

            damage.push_back(6); // updating damage

            if (getElement()=="FIRE"||getElement()=="WATER"||getElement()=="EARTH"||getElement()=="AIR"){
                type.push_back(getElement());
            }
            else{type.push_back("POISON");}

        }
        else if (getCategory()=="MYSTICAL"){

            damage.push_back(3); // updating damage

            if (getElement()=="FIRE"||getElement()=="WATER"||getElement()=="EARTH"||getElement()=="AIR"){
                type.push_back(getElement());
            }
            else{type.push_back("POISON");}
            
        }
        else if (getCategory()=="UNDEAD"){

            damage.push_back(3); // updating damage
            damage.push_back(1); // updating damage

            if (getElement()=="FIRE"||getElement()=="WATER"||getElement()=="EARTH"||getElement()=="AIR"){
                type.push_back(getElement());
            }
            else{type.push_back("POISON");}

            type.push_back("POISON");

        } 
        else if (getCategory()=="UNKNOWN"){

            damage.push_back(3); // updating damage

            if (getElement()=="FIRE"||getElement()=="WATER"||getElement()=="EARTH"||getElement()=="AIR"){
                type.push_back(getElement());
            }
            else{type.push_back("POISON");}
        } 
    }

    attack_.type_ =type; // populating the data
    attack_.damage_= damage;

    Creature::addAttack(attack_);
}
/**
 * @post: Displays available attacks and promps the user to enter 2 numbers in the range [1,3]
 *        Print in the following form:
 *        [DRAGON] Choose an attack (1-3):\n1: BITE\t\t2: STOMP\t\t3: ELEMENTAL BREATH\n
 */
void Dragon::displayAttacks() const
{
    std::cout << "[DRAGON]" << " Choose an attack (1-3):"<<std::endl;
    std::cout << "1: BITE         2: STOMP                3: ELEMENTAL BREATH"<<std::endl;
}