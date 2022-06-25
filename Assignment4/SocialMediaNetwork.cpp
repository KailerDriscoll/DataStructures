/************************************************************************/
/*                SocialMediaNetwork Implementation                     */
/************************************************************************/
/*    TODO: Implement the member functions of class SocialMediaNetwork  */
/*     This class uses a linked-list of SocialMediaProfile structs to   */
/*          represent communication paths between profiles              */
/************************************************************************/

#include "SocialMediaNetwork.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;


/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
SocialMediaNetwork::SocialMediaNetwork() {
    /* finished. do not touch. */
    head = NULL;
}

/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool SocialMediaNetwork::isEmpty()
{
/* finished. do not touch. */
    return (head == NULL);
}

/*
 * Purpose: Add a new profile to the network
 *   between the profile *previous and the profile that follows it in the network.
 * @param previous      -- name of the SocialMediaProfile that comes before the new profile
 * @param profileName   -- name of the new profile
 * @param totalFriends  -- number of friends of the profile
 * @param status        -- social media status 
 * @return none
 */
void SocialMediaNetwork::addProfileInfo(SocialMediaProfile* previous, string profileName, int totalFriends, string status){
    SocialMediaProfile* newProfile = new SocialMediaProfile();
    newProfile->name = profileName;
    newProfile->socialMediaStatus = status;
    newProfile->numberMessages = 0;
    newProfile->totalFriends = totalFriends;

    if (previous == NULL) {
        newProfile->next = head;
        head = newProfile;
        cout << "adding: " << profileName << " (HEAD)" << endl;
    } else {
        newProfile->next = previous->next;
        previous->next = newProfile;
        cout << "adding: " << profileName << " (prev: " << previous->name << ")" << endl;
    }
}


/*
 * Purpose: populates the network with the predetermined profiles
 * @param none
 * @return none
 */
void SocialMediaNetwork::loadDefaultSetup()
{
    deleteEntireNetwork();  // MODIFICATION: Use deleteEntireNetwork function before adding buildings
    addProfileInfo(NULL, "Marshall", 10, "There is a great sanwich place on 24th.");
    addProfileInfo(searchForProfile("Marshall"), "Lily", 8, "I want to move to the suburbs.");
    addProfileInfo(searchForProfile("Lily"), "Ted", 6, "Working on a building design right now.");
    addProfileInfo(searchForProfile("Ted"), "Robin", 5, "The Canucks won today.");
    addProfileInfo(searchForProfile("Robin"), "Barney", 4, "Suit up.");
    addProfileInfo(searchForProfile("Barney"), "Ranjit", 15, "NYC is an interesting city.");

}

/*
 * Purpose: Search the network for the specified profile and return a pointer to that node
 * @param profileName -- name of the profile to look for in network
 * @return pointer to node of profileName, or NULL if not found
 *
 */
SocialMediaProfile* SocialMediaNetwork::searchForProfile(string profileName)
{
    SocialMediaProfile* node = new SocialMediaProfile();
    node = head;
    while (node) {
        if (!node->name.compare(profileName)) {
            return node;
        }
        node = node->next;
    }
    return NULL;
}


/*
 * Purpose:
 * @param string receiver
 * @param string msg
 */
void SocialMediaNetwork::transmitNumFriendsInfo(string receiverProfileName) {
    SocialMediaProfile *node = new SocialMediaProfile;
    node = head;
    
    if (!node) {cout << "Empty list" << endl;}
    else if (searchForProfile(receiverProfileName) == NULL) {cout << "Profile not found" << endl;} 
    else {
        while (node != searchForProfile(receiverProfileName)->next) {
            node->numberMessages++;
            cout << node->name << " [# messages received: " << node->numberMessages << "] received: " << node->name << " has " << node->totalFriends << " friends." << endl;
            node = node->next;
        }
    }
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void SocialMediaNetwork::printNetwork() {
    SocialMediaProfile *current = head;
    cout << "== CURRENT PATH ==" << endl;
    while (current) {
        cout << current->name << "(" << current->totalFriends << ") -> ";
        current = current->next;
    }
    if (isEmpty()) {cout << "nothing in path" << endl;}
    else {cout << "NULL" << endl;}
    cout << "===" << endl;
}

/****************************************************/
/*  ASSIGNMENT 4: Functions to be completed below.  */
/****************************************************/

/*
 * Purpose: Delete the SocialMediaProfile in the network with the specified name.
 * @param profileName name of the SocialMediaProfile to delete in the network
 * @return none
 */
void SocialMediaNetwork::deleteSocialMediaProfile(string profileName) 
{
    SocialMediaProfile* node = new SocialMediaProfile();
    SocialMediaProfile* prev = new SocialMediaProfile();
    node = head;
    prev = NULL;
    while (node) {
        if (!node->name.compare(profileName)) {
            if (prev == NULL) {head = head->next;}
            else {prev->next = node->next;}
            delete node;
            node = nullptr;
            return;
        }
        prev = node;
        node = node->next;
    }
    cout << "Profile does not exist." << endl;
}

/*
 * Purpose: deletes all SocialMediaProfiles in the network starting at the head SocialMediaProfile.
 * @param: none
 * @return: none
 */
void SocialMediaNetwork::deleteEntireNetwork()
{
    while(!isEmpty()) {
        cout << "deleting: " << head->name << endl;
        deleteSocialMediaProfile(head->name);
    }
    head = NULL;
    cout << "Deleted network" << endl;
}

/*
* Purpose: Creates a loop from last node to the SocialMediaProfile specified.
* @param profileName name of the SocialMediaProfile to loop back
* returns the last node before loop creation (to break the loop)
*/
SocialMediaProfile* SocialMediaNetwork::createLoop(string profileName) 
{
    SocialMediaProfile* target = new SocialMediaProfile();
    SocialMediaProfile* end = new SocialMediaProfile();
    end = head;
    while (end->next) {
        end = end->next;
        if (!end->name.compare(profileName)) {
            target = end;
        }
    }
    cout << endl;
    end->next = target;
    return end;
}

/*
 * Purpose: to detect loop in the linked list
 * @return: true if loop is detected.
 */

bool SocialMediaNetwork::detectLoop() 
{
    SocialMediaProfile* slow = new SocialMediaProfile();
    SocialMediaProfile* fast = new SocialMediaProfile();
    slow = head;
    fast = head;
    while(slow->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow==fast) {return true;}
    }
    return false;
}

/*
 * Purpose: Take the chunk of nodes from start index to end index
 *          Move that chunk to the end of the List
 * @param: start index, end index
 * @return: none
 */
void SocialMediaNetwork::readjustNetwork(int start_index, int end_index)
{
    if (isEmpty()) {cout << "Linked List is Empty" << endl; return;}
    SocialMediaProfile *node = new SocialMediaProfile;
    SocialMediaProfile *first = new SocialMediaProfile;
    SocialMediaProfile *last = new SocialMediaProfile;

    SocialMediaProfile *temp = new SocialMediaProfile;

    node = head;
    first = head;
    last = head;
    int iterator = 0;
    int option = -1;
    while (node->next) {
        if (start_index == 0) {
            option = 1;
            first = head;
        } else if (start_index == iterator+1) {
            option = 2;
            first = node;
        }
        if (iterator == end_index) {
            last = node;
        }
        node = node->next;
        iterator++;
    }

    if (end_index>=iterator || end_index<0) {cout << "Invalid end index" << endl; return;}
    else if (start_index>iterator || start_index<0) {cout << "Invalid start index" << endl; return;}
    else if (start_index > end_index) {cout << "Invalid indices" << endl; return;}
    
    switch (option) {
        case 1:
            head = last->next;
            node->next = first;
            break;
        case 2:
            //temp = first->next;
            //last->next->next = first->next;
            node->next = first->next;
            first->next = last->next;
            //node->next = temp;
            break;
    }
    

    last->next = NULL;
}

/*
 * Purpose: Destructor to delete the entire list on termination
 * @param none
 * @return none
 */
SocialMediaNetwork::~SocialMediaNetwork()
{
    // TODO: Complete this function
}
