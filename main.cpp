//   https://github.com/cmilito/28.15/tree/abf4cb455052fef28666447091c42adb9aaf15d1
//   Christopher Milito

#include <iostream>
#include <string>
#include "PlaylistNode.h"

using namespace std;

void PrintMenu(const string playlistTitle) {
   cout << playlistTitle << " PLAYLIST MENU" << endl;
   cout << "a - Add song" << endl;
   cout << "d - Remove song" << endl;
   cout << "c - Change position of song" << endl;
   cout << "s - Output songs by specific artist" << endl;
   cout << "t - Output total time of playlist (in seconds)" << endl;
   cout << "o - Output full playlist" << endl;
   cout << "q - Quit" << endl;   
}

PlaylistNode* ExecuteMenu(char option, string playlistTitle, PlaylistNode* headNode) {
   while (option != 'q') {
      cin.ignore();
      if (option == 'a'){
         string id, songName, artistName;
         int songLength;
         
         cout << "ADD SONG" << endl;
         cout << "Enter song's unique ID:" << endl;
         cin >> id;
         cin.ignore();
         cout << "Enter song's name:" << endl;
         getline(cin, songName);
         cout << "Enter artist's name:" << endl;
         getline(cin, artistName);
         cout << "Enter song's length (in seconds):\n" << endl;
         cin >> songLength;
         
         PlaylistNode* newNode = new PlaylistNode(id, songName, artistName, songLength);
         
         if(headNode == nullptr){
            headNode = newNode;
         }
         else{
            PlaylistNode* currentNode = headNode;
            while (currentNode->GetNext() != nullptr){
               currentNode = currentNode->GetNext();
            }
            currentNode->SetNext(newNode);
         }
      }
      else if (option == 'd'){
         string id, title;
         cout << "REMOVE SONG" << endl;
         cout << "Enter song's unique ID:" << endl;
         cin >> id;
         
         PlaylistNode* currentNode = headNode;
         PlaylistNode* pastNode = nullptr;
         
         while((currentNode != nullptr)&&(currentNode->GetID() != id)){
            pastNode = currentNode;
            currentNode = currentNode->GetNext();
         }    
         title = currentNode->GetSongName();
         if (pastNode == nullptr) {
            headNode = currentNode->GetNext();
         } 
         else {
           pastNode->SetNext(currentNode->GetNext());
         }
         delete currentNode;
         cout << "\"" << title << "\" removed.\n" << endl;
      }
      else if (option == 't'){
         PlaylistNode* currentNode = headNode;
         int totalTime = 0;
         
         while(currentNode != nullptr){
            totalTime += currentNode->GetSongLength();
            currentNode = currentNode->GetNext();
         }
         
         cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
         cout << "Total time: " << totalTime << " seconds\n" << endl;
      }
      else if (option == 'o'){
         int i = 1;
         PlaylistNode* currentNode = headNode;
         cout << playlistTitle << " - OUTPUT FULL PLAYLIST" << endl;

         if (headNode == nullptr) {
            cout << "Playlist is empty\n" << endl;
         }
         else {
            while (currentNode != nullptr) {
               cout << i << "." << endl;
               currentNode->PrintPlaylistNode();
               cout << endl;
               currentNode = currentNode->GetNext();
               ++i;
            }
         }
   }
      else if(option == 's'){
         PlaylistNode* currentNode = headNode;
         int i = 1;
         string artistName;

         cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
         cout << "Enter artist's name:\n" << endl;
         cin >> ws;
         getline(cin, artistName);

         while (currentNode != nullptr) {
            if (currentNode->GetArtistName() == artistName) {
               cout << i << "." << endl;
               currentNode->PrintPlaylistNode();
               cout << endl;
            }
          ++i;
         currentNode = currentNode->GetNext();
         }
   }
      else if(option == 'q'){
         break;
      }    
      PrintMenu(playlistTitle);
      cout << "\nChoose an option:" << endl;
      cin >> option;
   }
   return headNode;
}

int main() {
   string playlistTitle;
   char option;
   PlaylistNode* headNode = nullptr;
   cout << "Enter playlist's title:\n" << endl;
   getline(cin >> ws, playlistTitle);
   
      PrintMenu(playlistTitle);
      cout << "\nChoose an option:" << endl;
      cin >> option;
      
      headNode = ExecuteMenu(option, playlistTitle, headNode);
   return 0;
}
