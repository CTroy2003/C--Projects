
/*
 *
 * This code is copyrighted (c) 2021 by
 * Texas A&M Computer Science
 *
 *	There will be RIGOROUS cheat checking on your exams!!
 *	DON'T POST ANYWHERE!! such as CHEGG, public Github, etc
 *  You will be legally responsible.
 */

#include <iostream>
#include <sstream>
#include <stdexcept>
#include "Network.h"
#include <fstream>
#include <string>
#include <sstream>
using std::cout;
using std::string;
using std::vector;
using std::ifstream;
using std::stringstream;
using std::endl;
using namespace std;

Network::Network() {
  // empty containers of vectors already created
  // no implementation is needed here
}

void Network::loadFromFile(string fileName) {
  // TODO(student): load user and post information from file
  ifstream infile;
  infile.open(fileName);

  if (infile.is_open() == false){
    throw std::invalid_argument("");
  }

  string file_line;
try{
  while (getline(infile, file_line)){
    string post_text;
    string word;
    string type;
    string username;
    unsigned int post_id;
    stringstream ss;

    ss << file_line;
    ss >> type;

    if (type == "User") {
      ss >> username;
      addUser(username);
    }
    
    if (type == "Post") {
      ss >> post_id;
      ss >> username;
      while (ss >> word){
        post_text = post_text + " " + word;
      }
      addPost(post_id, username, post_text);
    }
  }
}
  catch(...){
    throw std::runtime_error("");
  }
}

void Network::addUser(string userName) {
  // TODO(student): create user and add it to network
  string user_copy = userName;

    for (int i = 0; i < user_copy.length(); i++) {
        user_copy[i] = tolower(user_copy[i]);
    }

    for (int i = 0; i < users.size(); i++) {
        if (users[i] -> getUserName() == user_copy) {
            throw std::invalid_argument("");
        }
    }

    
    User *new_user = new User(userName); 
    users.push_back(new_user); 
    cout << "Added User " << userName << '\n';
}

void Network::addPost(unsigned int postId, string userName, string postText) {
  // TODO(student): create post and add it to network
  for (int i = 0; i < posts.size(); i++) {
        if (posts[i] -> getPostId() == postId) {
            throw std::invalid_argument("Post Id already exists");
        }
    }
    int index = 0;
    bool existing_user = false; 

    for (int i = 0; i < users.size(); i++) {
      if (users[i] -> getUserName() == userName) {
        index = i;
        existing_user = true;
      }
    }

    
    if (existing_user == false) {
        throw std::invalid_argument("");
    }

    Post * new_post = new Post(postId, userName, postText);
    posts.push_back(new_post); 
    users[index] -> addUserPost(new_post); 

    vector<string> new_tags = new_post -> findTags();
    
    for (int i = 0; i < new_tags.size(); i++) {
        bool tag_found = false;
        // iterate through tags
        for (int j = 0; j < tags.size(); j++) {
            // if identical tag found
            if (new_tags[i] == tags[j] -> getTagName()) {
                tag_found = true;
                // add tags
                tags[j] -> addTagPost(new_post);
            }
        }
        // try and catch block
        try {
            // if tag found
            if (tag_found == false) {
                // create new tag
                Tag *new_tag = new Tag(new_tags[i]);
                tags.push_back(new_tag); // add to tags
                tags.back() -> addTagPost(new_post);
            }
        // catch the exception
        }
        catch (exception & exc){
          cout<<"Error occured"<<endl;
          cout<< exc.what()<<endl;
        }
    }

  
        
    cout << "Added Post " << postId << " by " << userName << '\n';
}

vector<Post*> Network::getPostsByUser(string userName) {
  // TODO(student): return posts created by the given user
  int flag = 1;
  if (userName == "") {
      throw std::invalid_argument("");
    }

  if(flag==1){
    for (int i = 0; i < users.size(); i++) {
      if (users[i] -> getUserName() == userName) {
         return users[i] -> getUserPosts();
      }
    }
  }
  flag = 0;
  throw std::invalid_argument("");
}

vector<Post*> Network::getPostsWithTag(string tagName) {
  // TODO(student): return posts containing the given tag
  bool tag_present = false;

  for (int i = 0; i < tags.size();++i){
    if (tags[i]->getTagName() == tagName){
      tag_present = true;
      return tags[i]->getTagPosts();
    }
  }

  if (tag_present == false){
    throw std::invalid_argument("");
  }
}

vector<string> Network::getMostPopularHashtag() {
  // TODO(student): return the tag occurring in most posts
  int max_occurence = 0;
  vector<string> tag_popularity;
  for (int i = 0; i < tags.size(); ++i){
    if (tags[i]->getTagPosts().size() >= max_occurence){
      max_occurence = tags[i]->getTagPosts().size();
    }
  }

  for (int i = 0; i < tags.size(); ++i){
    if (tags[i]->getTagPosts().size() == max_occurence){
      max_occurence = tags[i]->getTagPosts().size();
      tag_popularity.push_back(tags[i]->getTagName());
    }
  }


  return tag_popularity;
}

/**
  * Destructor
  * Do not change; already implemented.
  */
Network::~Network() {
  for (unsigned int i = 0; i < users.size(); ++i) {
    delete users.at(i);
  }
  for (unsigned int i = 0; i < tags.size(); ++i) {
    delete tags.at(i);
  }
  for (unsigned int i = 0; i < posts.size(); ++i) {
    delete posts.at(i);
  }
}

