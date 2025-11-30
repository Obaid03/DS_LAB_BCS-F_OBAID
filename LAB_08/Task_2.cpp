#include<iostream>
#include<string>
using namespace std;
class Combatant {
public:
    string name;
    int hp;
    int attack;
    int id;

    Combatant() {}

    Combatant(int i, string n, int h, int a){
        id = i;
        name = n;
        hp = h;
        attack = a;
    }
};

class Node {
public:
    Combatant key;
    Node *left;
    Node *right;

    Node(Combatant k) : key(k) {
        left = right = NULL;
    }
};

class BSTree {
private:
    Node *head;
    int nodeCount;

    Node* insert(Node *curr, Combatant value){
        if(curr == NULL){
            return new Node(value);
        }

        if(value.id < curr->key.id){
            curr->left = insert(curr->left, value);
        }
        else if(value.id > curr->key.id){
            curr->right = insert(curr->right, value);
        }
        return curr;
    }

    Node* deleteNode(Node *curr, int value) {
        if(curr == NULL) return curr;

        if(value < curr->key.id)
            curr->left = deleteNode(curr->left, value);

        else if(value > curr->key.id)
            curr->right = deleteNode(curr->right, value);

        else {
            if (curr->left == NULL && curr->right == NULL) {
                delete curr;
                return NULL;
            }
            else if(curr->left == NULL) {
                Node *temp = curr->right;
                delete curr;
                return temp;
            }
            else if(curr->right == NULL) {
                Node *temp = curr->left;
                delete curr;
                return temp;
            }
            else{
                Node *temp = minimum(curr->right);
                curr->key = temp->key;
                curr->right = deleteNode(curr->right, temp->key.id);
            }
        }
        return curr;
    }

    bool SearchNode(Node *curr, int value) {
        if(curr == NULL) return false;

        if(curr->key.id == value)
            return true;
        else if(value < curr->key.id)
            return SearchNode(curr->left, value);
        else
            return SearchNode(curr->right, value);
    }

public:

    BSTree(){
        head = NULL;
        nodeCount = 0;
    }

    void inorder(Node *curr){
        if(curr != NULL){
            inorder(curr->left);
            cout << curr->key.name << " --> " << curr->key.hp << " HP ";
            inorder(curr->right);
        }
    }

    Node* minimum(Node *curr) {
        while(curr && curr->left != NULL){
            curr = curr->left;
        }
        return curr;
    }

    void insert(Combatant value) {
        head = insert(head, value);
    }

    void display(){
        inorder(head);
        cout << endl;
    }

    void Delete(int value) {
        head = deleteNode(head, value);
    }

    bool search(int value) {
        return SearchNode(head, value);
    }

    bool isEmpty(){
        return head == NULL;
    }

    Node* frontline(){
        return minimum(head);
    }
};

class Game {
private:
    BSTree heroes;
    BSTree enemies;
    int round;

public:

    Game(){
        round = 1;
        loadHeroes();
        loadEnemies();
    }

    void loadHeroes(){
        heroes.insert( Combatant(1, "Knight", 40, 8) );
        heroes.insert( Combatant(2, "Archer", 35, 10) );
        heroes.insert( Combatant(3, "Mage", 30, 12) );
        heroes.insert( Combatant(4, "Paladin", 45, 7) );
        heroes.insert( Combatant(5, "Rogue", 32, 11) );
    }

    void loadEnemies(){
        enemies.insert( Combatant(10, "Goblin", 25, 6) );
        enemies.insert( Combatant(11, "Orc", 40, 9) );
        enemies.insert( Combatant(12, "Dark Mage", 35, 11) );
        enemies.insert( Combatant(13, "Skeleton", 28, 7) );
        enemies.insert( Combatant(14, "Dragonling", 50, 13) );
    }

    void startBattle(){
        while(!heroes.isEmpty() && !enemies.isEmpty()){
            playRound();
            round++;
        }

        if(heroes.isEmpty())
            showWinner("Enemies");
        else
            showWinner("Heroes");
    }

    void playRound(){
        cout << " ROUND " << round <<endl;
        showStatus();

        heroAttack();

        if(enemies.isEmpty())
            return;

        enemyAttack();
    }

    void heroAttack(){
        Node *hero = heroes.frontline();
        Node *enemy = enemies.frontline();

        int damage = calculateDamage(hero->key.attack);

        cout << "\n" << hero->key.name << " attacks " << enemy->key.name;
        cout << " for " << damage << " damage"<<endl;

        enemy->key.hp -= damage;

        if(enemy->key.hp <= 0){
            showElimination(enemy->key.name);
            enemies.Delete(enemy->key.id);
        }
        else{
            cout << enemy->key.name <<"now has " 
                 << enemy->key.hp <<" HP"<<endl;
        }
    }

    void enemyAttack(){
        Node *hero = heroes.frontline();
        Node *enemy = enemies.frontline();

        int damage = calculateDamage(enemy->key.attack);

        cout <<enemy->key.name<<"attacks"<< hero->key.name;
        cout << " for " << damage << " damage"<<endl;

        hero->key.hp -= damage;

        if(hero->key.hp <= 0){
            showElimination(hero->key.name);
            heroes.Delete(hero->key.id);
        }
        else{
            cout << hero->key.name <<"now has" 
                 << hero->key.hp << " HP"<<endl;
        }
    }

    int calculateDamage(int baseAttack){
        return baseAttack + 2;
    }

    void showStatus(){
        cout << "Heroes: ";
        heroes.display();

        cout << "Enemies: ";
        enemies.display();
    }

    void showElimination(string name){
        cout << name << " has been defeated and removed from the battlefield"<<endl;
    }

    void showWinner(string teamName){
        cout << teamName << " Won the battale"<< endl;
    }
};

int main(){
    Game arena;
    arena.startBattle();
    return 0;
}