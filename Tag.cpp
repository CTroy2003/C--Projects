/*
 *
 * This code is copyrighted (c) 2021 by
 * Texas A&M Computer Science
 *
 *	There will be RIGOROUS cheat checking on your exams!!
 *	DON'T POST ANYWHERE!! such as CHEGG, public Github, etc
 *  You will be legally responsible.
 */

#include <string>
#include <stdexcept>
#include "Tag.h"
#include <cctype>

using std::string;
using std::vector;

Tag::Tag(string tagName) /* TODO(student): initialize */ {
  // TODO(student): implement constructor checks
  if (tagName.length() < 2 || tagName[0] != '#' ||
      !(tagName[1] >= 97 && tagName[1] <= 122) ||
      tagName[tagName.length()-1] == '!' || tagName[tagName.length()-1] == ',' || 
      tagName[tagName.length()-1] == '.' || tagName[tagName.length()-1] == '?'){
        throw std::invalid_argument("");
      }
  for (int i = 1; i < tagName.length(); ++i){
    if (isupper(tagName[i])){
      throw std::invalid_argument("tagName contains an upper case letter");
    }
  }
  this -> tagName = tagName;
}

string Tag::getTagName() {
  // TODO(student): implement getter
  return tagName;
}

vector<Post*>& Tag::getTagPosts() {
  // TODO(student): implement getter
  return tagPosts;
}

void Tag::addTagPost(Post* post) {
  // TODO(student): add post to tag posts
  if (post == nullptr){
    throw std::invalid_argument("post is nullptr");
  }
    else{
      tagPosts.push_back(post);
    }
}
