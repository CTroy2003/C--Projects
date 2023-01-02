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
#include <string>
#include <stdexcept>
#include "Post.h"
#include <sstream>
#include <cctype>
using namespace std;
using std::string;
using std::vector;
using std::stringstream;

Post::Post(unsigned int postId, string userName, string postText)
  : postId(postId), userName(userName), postText(postText) {
  if (postId == 0 || userName == "" || postText == "") {
    throw std::invalid_argument("post constructor: invalid parameter values");
  }
  this->userName = userName;
  this->postId = postId;
  this->postText = postText;
}

unsigned int Post::getPostId() {
  return postId;
}

string Post::getPostUser() {
  return userName;
}

string Post::getPostText() {
  return postText;
}

vector<string> Post::findTags() {
  // TODO(student): extracts candidate tags based on occurrences of # in the post
  stringstream ss;

    // get post text string
    string post_text = getPostText();
    ss.str(post_text);

    // for storing word
    string str;

    vector<string> post_tags;

    // for each words in the post text string
    while (ss >> str) {
        // if word start with #
        if (str[0] == '#') {
            // convert to lower case string
            for (int i = 1; i < str.length(); i++) {
                str[i] = tolower(str[i]);
            }

            // if word has punctiations at end then remove them
            while (str[str.length()-1] == '!' || str[str.length()-1] == ',' 
                    || str[str.length()-1] == '.' || str[str.length()-1] == '?') {
                str.pop_back(); 
            }

            
            post_tags.push_back(str);
        }
    }
    return post_tags;
}
