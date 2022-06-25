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
void SocialMediaNetwork::loadDefaultSetup(){
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
SocialMediaProfile* SocialMediaNetwork::searchForProfile(string profileName){
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
