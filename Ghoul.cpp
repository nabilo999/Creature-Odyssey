/*
CSCI235 Spring 2024
Project 4 - MycoMorsels
Georgina Woo
Dec 24 2023
Ghoul.cpp implements the constructors and private and public functions of the Ghoul class
*/
// Nabil Said
// nabil.said54@myhunter.cuny.edu
// CSCI 235 - Project 1
// Prof: Tiziana Ligorio
#include "Ghoul.hpp"

Ghoul::Ghoul() :  decay_{0}, faction_{NONE}, transformation_{false}
{
    setCategory(UNDEAD); 
}

Ghoul::Ghoul(const std::string& name, Category category, int hitpoints, int level, bool tame, int decay, Faction faction, bool transformation) : Creature(name, category, hitpoints, level, tame)
{
    if(!setDecay(decay))
    {
        decay_ = 0;
    }
    faction_ = faction;
    transformation_ = transformation;
}

int Ghoul::getDecay() const
{
    return decay_;
}

bool Ghoul::setDecay(const int& decay)
{
    if(decay >= 0)
    {
        decay_ = decay;
        return true;
    }
    else
    {
        return false;
    }
}

std::string Ghoul::getFaction() const
{
    switch(faction_)
    {
        case FLESHGORGER:
            return "FLESHGORGER";
        case SHADOWSTALKER:
            return "SHADOWSTALKER";
        case PLAGUEWEAVER:
            return "PLAGUEWEAVER";
        default:
            return "NONE";
    }
}

void Ghoul::setFaction(const Faction& faction)
{
    faction_ = faction;
}

bool Ghoul::getTransformation() const
{
    return transformation_;
}

void Ghoul::setTransformation(const bool& transformation)
{
    transformation_ = transformation;
}


/**
    @post     : displays Ghoul data in the form:
    GHOUL - [NAME]\n
    CATEGORY: [CATEGORY]\n
    HP: [HITPOINTS]\n
    LVL: [LEVEL]\n
    TAME: [TAME]\n
    DECAY: [DECAY]\n
    FACTION: [FACTION]\n
    IT [CAN/CANNOT] TRANSFORM\n"
    
    Example:
    
*/
void Ghoul::display() const
{
    std::cout << "GHOUL - " << getName() << std::endl;
    std::cout << "CATEGORY: " << getCategory() << std::endl;
    std::cout << "HP: " << getHitpoints() << std::endl;
    std::cout << "LVL: " << getLevel() << std::endl;
    std::cout << "TAME: " << (isTame() ? "TRUE" : "FALSE") << std::endl;
    std::cout << "DECAY: " << getDecay() << std::endl;
    std::cout << "FACTION: " << getFaction() << std::endl;
    std::cout << "IT " << (getTransformation() ? "CAN" : "CANNOT") << " TRANSFORM" << std::endl;
}


bool Ghoul::eatMycoMorsel()
{
    if(getCategory() == "UNDEAD")
    {
        setTame(true);
        setHitpoints(getHitpoints() + 1);
        return false;
    }
    else if(getFaction() == "FLESHGORGER")
    {
        if(isTame())
        {
            setTame(false);
            return false;
        }
        else
        {
            return true;
        }
    }
    else if(getFaction() == "SHADOWSTALKER")
    {
        if(isTame())
        {
            if(getHitpoints() == 1)
            {
                setTame(false);
            }
            else
            {
                setHitpoints(getHitpoints() - 1);
            }
            return false;
        }
        else
        {
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
        * Here are the attacks for the Ghoul:
        * 
        * 1: Attack name: BITE
        *   if ALIEN: 4 PHYSICAL
        *   if MYSTICAL: 
        *      if FLESHGORGER: 2 PHYSICAL
        *      if SHADOWSTALKER: 2 PHYSICAL, 1 VOID
        *      if PLAGUEWEAVER: 2 PHYSICAL, 1 POISON
        *      if NONE: 2 PHYSICAL
        *  if UNDEAD: 2 PHYSICAL, 1 POISON
        *  if UNKNOWN: 2 PHYSICAL
        * 
        * 2: 
        *  if FLESHGORGER/NONE: 
        *      Attack name: CLAW
        *      2 PHYSICAL
        *  if SHADOWSTALKER:
        *     Attack name: SLASH
        *     2 PHYSICAL, 1 VOID
        * if PLAGUEWEAVER:
        *    Attack name: INFECT
        *    2 PHYSICAL, 1 POISON
        * 
        * 3:
        *  if FLESHGORGER/NONE:
        *     Attack name: FLY SWARM
        *     3 PHYSICAL
        * if SHADOWSTALKER:
        *     Attack name: SHROUD OF DARKNESS
        *     2 PHYSICAL, 1 VOID
        * if PLAGUEWEAVER:
        *     Attack name: PLAGUE CLOUD
        *     2 PHYSICAL, 1 POISON
        *  
*/
void Ghoul::addAttack(const int &attack)
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

            if(getFaction()== "FLESHGORGER"){
                type.push_back("PHYSICAL"); // updating type
                damage.push_back(2);// updating damage
            }
            else if(getFaction()== "SHADOWSTALKER"){
                type.push_back("PHYSICAL"); // updating type
                type.push_back("VOID"); // updating type
                damage.push_back(2);// updating damage
                damage.push_back(1);// updating damage
            }
            else if(getFaction()== "PLAGUEWEAVER"){
                type.push_back("PHYSICAL"); // updating type
                type.push_back("POISON"); // updating type
                damage.push_back(2);// updating damage
                damage.push_back(1);// updating damage
            }
            else if(getFaction()== "NONE"){
                type.push_back("PHYSICAL"); // updating type
                damage.push_back(2);// updating damage
            }
            
        }
        else if (getCategory()=="UNDEAD"){

            type.push_back("PHYSICAL"); // updating type
            damage.push_back(2); // updating damage
            type.push_back("POISON"); // updating type
            damage.push_back(1); // updating damage

        } 
        else if (getCategory()=="UNKNOWN"){

            type.push_back("PHYSICAL"); // updating type

            damage.push_back(2); // updating damage
        }
    }

    else if (attack ==2){

        if (getFaction()=="FLESHGORGER" || getFaction()=="NONE"){

            attack_.name_= "CLAW"; // updating name

            type.push_back("PHYSICAL"); // updating type

            damage.push_back(2); // updating damage
        }
        else if (getFaction()=="SHADOWSTALKER"){

            attack_.name_= "SLASH"; // updating name

            type.push_back("PHYSICAL"); // updating type
            damage.push_back(2); // updating damage

            type.push_back("VOID"); // updating type
            damage.push_back(1); // updating damage

        }
        else if (getFaction()=="PLAGUEWEAVER"){

            attack_.name_= "INFECT"; // updating name
            
            type.push_back("PHYSICAL"); // updating type
            type.push_back("POISON"); // updating type

            damage.push_back(2); // updating damage
            damage.push_back(1); // updating damage
        } 
    }

    else if (attack ==3){
        if (getFaction()=="FLESHGORGER" || getFaction()=="NONE"){

            attack_.name_= "FLY SWARM"; // updating name

            type.push_back("PHYSICAL"); // updating type

            damage.push_back(3); // updating damage
        }
        else if (getFaction()=="SHADOWSTALKER"){

            attack_.name_= "SHROUD OF DARKNESS"; // updating name

            type.push_back("PHYSICAL"); // updating type
            damage.push_back(2); // updating damage
            
            type.push_back("VOID"); // updating type
            damage.push_back(1); // updating damage

        }
        else if (getFaction()=="PLAGUEWEAVER"){

            attack_.name_= "PLAGUE CLOUD"; // updating name
            
            type.push_back("PHYSICAL"); // updating type
            type.push_back("POISON"); // updating type

            damage.push_back(2); // updating damage
            damage.push_back(1); // updating damage
        } 
    }

    attack_.type_ =type; // populating the data
    attack_.damage_= damage;

    Creature::addAttack(attack_);

}

/**
    @post     : displays the attacks of the Ghoul in the form:
    [GHOUL] Choose an attack (1-3):\n1: BITE\t\t2: CLAW\t\t3: CLOUD OF DOOM\n
*/
void Ghoul::displayAttacks() const
{
    std::cout << "[GHOUL]" << " Choose an attack (1-3):"<<std::endl;
    std::cout << "1: BITE         2: CLAW         3: CLOUD OF DOOM "<<std::endl;

}