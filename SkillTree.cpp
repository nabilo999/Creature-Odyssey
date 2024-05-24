#include "SkillTree.hpp"
/**
 * Parameterized constructor
 * @param id: The unique identifier for the Skill
 * @param name: The name of the Skill
 * @param description: The description of the Skill
 * @param leveled: Whether or not the Skill is leveled up
*/
Skill::Skill()
{
}
Skill::Skill(int id, std::string name, std::string description, bool leveled)
{
  id_=id;
  name_=name;
  description_=description;
  leveled_=leveled;
}

/**
  * @param: A const reference to Skill 
  * @return: True if the id_ of the Skill is equal to that of the argument, false otherwise
*/
bool Skill::operator==(const Skill &rhs) const
{
  return (id_ == rhs.id_);
}

/**
  * @param: A const reference to Skill 
  * @return: True if the id_ of the Skill is less than that of the argument, false otherwise
*/
bool Skill::operator<(const Skill &rhs) const
{
  return (id_ < rhs.id_);
}

/**
  * @param: A const reference to Skill 
  * @return: True if the id_ of the Skill is greater than that of the argument, false otherwise
*/
bool Skill::operator>(const Skill &rhs) const
{
  return (id_ > rhs.id_);
}

/**
    Default Constructor
*/
SkillTree::SkillTree() 
{
}

/**
 * @param: A const reference to string: the name of a csv file
 * @post: The SkillTree is populated with Skills from the csv file
 * The file format is as follows:
 * id,name,description,leveled
 * Ignore the first line. Each subsequent line represents a Skill to be added to the SkillTree.
*/
SkillTree::SkillTree(const std::string &filename)
{
    std::ifstream fin(filename);
    std::string line;
    std::getline(fin, line); // Ignore the header

    while(std::getline(fin, line)) {
        std::istringstream iss(line);
        std::string str_id, name, description, str_leveled;

        std::getline(iss, str_id, ',');
        std::getline(iss, name, ',');
        std::getline(iss, description, ',');
        std::getline(iss, str_leveled, ',');

        int id = std::stoi(str_id);
        bool leveled = (str_leveled == "1"); 

        // Create Skill object and add to SkillTree
        Skill skill(id, name, description, leveled);

        // Add skill to the SkillTree 
        addSkill(skill);
    }

}

/**
 * @param: A const reference to int representing the id of the Skill to be found
 * @return: A pointer to the node containing the Skill with the given id, or nullptr if the Skill is not found
*/
std::shared_ptr<BinaryNode<Skill>> SkillTree::findSkill(const int& id) const {
    return findSkillHelper(getRoot(), id);
}

std::shared_ptr<BinaryNode<Skill>> SkillTree::findSkillHelper(std::shared_ptr<BinaryNode<Skill>> subtree_ptr, const int &id) const
{
    if (subtree_ptr == nullptr) {// Skill not found
        return nullptr;
    }

    else if (subtree_ptr->getItem().id_ == id) {// Skill found
        return subtree_ptr;
    }

    else if (subtree_ptr->getItem().id_ > id) {// Search left subtree
        return findSkillHelper(subtree_ptr->getLeftChildPtr(), id);
    } 

    else {// Search right subtree
        return findSkillHelper(subtree_ptr->getRightChildPtr(), id);
    }
}

/**
  * @param: A const reference to Skill 
  * @post: The Skill is added to the tree (in BST order as implemented in the base class) only if it was not already in the tree. Note that all comparisons are id-based as implemented by the Skill comparison operators.
  * @return: True if the Skill is successfully added to the SkillTree, false otherwise
  */
bool SkillTree::addSkill(const Skill &skill)
{
    if (contains(skill)) {// Skill already exists, return false
        return false;
    } else {// Skill does not exist, add it to the tree
        add(skill);
        return true;
    }
    return false;
}

/**
  * @param: A const reference to string: the name of a Skill
  * @return: True if the Skill is successfully removed from the SkillTree, false otherwise
*/
bool SkillTree::removeSkill(const std::string name)
{
    std::shared_ptr<BinaryNode<Skill>> skill = removeSkillHelper(getRoot(), name);
    if (skill == nullptr) { // Skill not found, return false
        return false;
    } else { // Skill found, remove it from the tree
        remove(skill->getItem());
        return true;
    }
}


std::shared_ptr<BinaryNode<Skill>> SkillTree::removeSkillHelper(std::shared_ptr<BinaryNode<Skill>> subtree_ptr, const std::string& name) const {
    if (subtree_ptr==nullptr){return nullptr;} // check if the given tree is empty

    else if (subtree_ptr->getItem().name_ == name) { // Skill found
      return subtree_ptr;
    }
    
    // Recursively search in left and right subtrees
    std::shared_ptr<BinaryNode<Skill>> left_result = removeSkillHelper(subtree_ptr->getLeftChildPtr(), name);
    std::shared_ptr<BinaryNode<Skill>> right_result = removeSkillHelper(subtree_ptr->getRightChildPtr(), name);

    if (left_result != nullptr && left_result->getItem().name_ == name) { // If found in left subtree, return it
      return left_result;
    }

    // If not found in left subtree, return result of right subtree search
    else if(right_result != nullptr && right_result->getItem().name_ == name){
      return right_result;
    }
    else{return nullptr;}
}

/**
  * @post: Clears the tree
*/
void SkillTree::clear()
{
    clearHelper(root_ptr_);
    root_ptr_ = nullptr; // Reset the root pointer after clearing the tree
}

void SkillTree::clearHelper(std::shared_ptr<BinaryNode<Skill>> subtree_ptr) {
    if (subtree_ptr != nullptr) {//using Post order to traverse and delete each node

        // Recursively clear left and right subtrees
        clearHelper(subtree_ptr->getLeftChildPtr());
        clearHelper(subtree_ptr->getRightChildPtr());
        
        // Delete the current node
        subtree_ptr.reset();
    }
}

/**
  * @param: A const reference to int representing the id of a Skill
    * Note: For a Skill to be leveled up, its parent Skill must also be leveled up, thus the Skill points are the number of Skills that must be leveled up before and including the Skill with the given id.
  * @return: an integer: the number of skill points needed to level up the Skill with the given id, starting from the root (i.e. the number of nodes from root to the given Skill).
  * Include the Skill with the given id in the count. For example, if the tree contains the following Skills (represented by their ids):
  *   5
  *  / \
  * 1   8
  * and the function parameter queries for id 8, the function should return 2.
  * Disregard the leveled_ field of the existing Skills in the tree.
  * If the Skill with the given id is not found, return -1.
  */
int SkillTree::calculateSkillPoints(const int& id) const {
    // Start the traversal from the root
    return calculateSkillPointsHelper(root_ptr_, id, 0);
}

int SkillTree::calculateSkillPointsHelper(std::shared_ptr<BinaryNode<Skill>> subtree_ptr, const int& id, int count) const {
    if (subtree_ptr == nullptr) {// Skill with given id not found
        return -1;
    } 
    else if (subtree_ptr->getItem().id_ == id) {// Skill with given id found, return the count
        return count +1 ;
    } 
    else if (subtree_ptr->getItem().id_ > id) {// Search left subtree
        return calculateSkillPointsHelper(subtree_ptr->getLeftChildPtr(), id, count + 1);
    } 
    else {// Search right subtree
        return calculateSkillPointsHelper(subtree_ptr->getRightChildPtr(), id, count + 1);
    }
}

/**
  * @post: Balances the tree. Recall the definition of a balanced tree:
  * A tree is balanced if for any node, its left and right subtrees differ in height by no more than 1. * All paths from root of subtrees to leaf differ in length by at most 1
  * Hint: You may sort the elements and build the tree recursively using a divide and conquer approach      
  */
void SkillTree::balance() {
    // Create a vector to store all skills
    std::vector<Skill> skills;
    // Traverse the tree in-order to collect all skills
    inorderTraversal(root_ptr_, skills);
    // Clear the tree
    clear();
    // Build a balanced tree from the sorted vector of skills
    root_ptr_ = rebuildBalanced(skills, 0, skills.size() - 1);
}

void SkillTree::inorderTraversal(std::shared_ptr<BinaryNode<Skill>> subtree_ptr, std::vector<Skill>& skills) const {
    if (subtree_ptr != nullptr) {
        inorderTraversal(subtree_ptr->getLeftChildPtr(), skills);
        // Add the current skill to the vector
        skills.push_back(subtree_ptr->getItem());
        inorderTraversal(subtree_ptr->getRightChildPtr(), skills);
    }
}

std::shared_ptr<BinaryNode<Skill>> SkillTree::rebuildBalanced(const std::vector<Skill>& skills, int start, int end) {
    if (start > end) {
        // Base case: no skills to add
        return nullptr;
    }

    // Find the middle index of the vector
    int mid = (start + end) / 2;

    // Create a new node with the skill at the middle index
    std::shared_ptr<BinaryNode<Skill>> newNode = std::make_shared<BinaryNode<Skill>>(skills[mid]);

    // Recursively build the left and right subtrees
    newNode->setLeftChildPtr(rebuildBalanced(skills, start, mid - 1));
    newNode->setRightChildPtr(rebuildBalanced(skills, mid + 1, end));

    return newNode;
}
/**
  * @post: prints the tree in preorder, in the format:
  [id_] [name_]\n
  [description_]\n 
  [leveled_]
*/
void SkillTree::preorderDisplay() const
{
  preorderDisplayhelper(getRoot());
}
void SkillTree::preorderDisplayhelper(std::shared_ptr<BinaryNode<Skill>> r) const
{ //root->left->right

  while(r==nullptr){return;}//check if tree is empty

  // print the root of subtree that we are on)
  std::cout<< r->getItem().id_<<" "<<r->getItem().name_<<std::endl;
  std::cout<< r->getItem().description_<<std::endl;
  std::cout<< r->getItem().leveled_<<std::endl;
  
  // recursively displays left and right subtree 
  preorderDisplayhelper(r->getLeftChildPtr());
  preorderDisplayhelper(r->getRightChildPtr());

}