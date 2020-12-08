#include "SocialNetwork.h"

#include <iostream>

SocialNetwork::SocialNetwork() {

}

void SocialNetwork::addProfile(const std::string& firstname, const std::string& lastname, const std::string& email) {
    Profile newProfile;
    newProfile = Profile(firstname, lastname, email);
    profiles.insertSorted(newProfile);
}

void SocialNetwork::addPost(const std::string& message, const std::string& email) {

    Node<Profile>* current;
    Post* newpost_p, newpost;


    newpost = Post(message);
    posts.insertAtTheTail(newpost);
    newpost_p = &(posts.getLastNode()->data);
    for (current = profiles.getFirstNode(); current; current = current->next) {

        if ((current->data).getEmail() == email) {

            ((current->data).getPosts()).insertAtTheTail(newpost_p);
            break;
        }
    }




}

void SocialNetwork::makeFriends(const std::string& email1, const std::string& email2) {
    Node<Profile>* current;
    Profile* pro1 = nullptr, * pro2 = nullptr;

    for (current = profiles.getFirstNode(); current && (!(pro1 && pro2)); current = current->next) {
        if ((current->data).getEmail() == email1) {
            pro1 = &(current->data);
        }
        if ((current->data).getEmail() == email2) {
            pro2 = &(current->data);
        }
    }

    ((pro1)->getFriends()).insertAtTheTail(pro2);
    ((pro2)->getFriends()).insertAtTheTail(pro1);


}

void SocialNetwork::likePost(int postId, const std::string& email) {
    Node<Post>* tra;
    Node<Profile>* current;
    Post* liked = nullptr;
    Profile* pro = nullptr;

    for (tra = posts.getFirstNode(); tra && (!liked); tra = tra->next) {
        if (tra->data.getPostId() == postId) {
            liked = &(tra->data);
        }
    }
    for (current = profiles.getFirstNode(); current && (!pro); current = current->next) {
        if ((current->data).getEmail() == email) {
            pro = &(current->data);
        }
    }
    (pro->getLikes()).insertAtTheTail(liked);
}

void SocialNetwork::unlikePost(int postId, const std::string& email) {
    Node<Post>* tra;
    Node<Profile>* current;
    Post* liked = nullptr;
    Profile* pro = nullptr;

    for (current = profiles.getFirstNode(); current && !pro; current = current->next) {
        if ((current->data).getEmail() == email) {
            pro = &(current->data);
        }
    }
    for (tra = posts.getFirstNode(); tra && !liked; tra = tra->next) {
        if ((tra->data).getPostId() == postId) {
            liked = &(tra->data);
        }
    }

    pro->getLikes().removeNode(liked);
}

LinkedList<Profile*> SocialNetwork::getMutualFriends(const std::string& email1, const std::string& email2) {
    LinkedList<Profile*> ret;
    Node<Profile>* cur;
    Node<Profile*>* fr1, * fr2;
    Profile* common, * pro1, * pro2;

    for (cur = profiles.getFirstNode(); cur; cur = cur->next) {
        if ((cur->data).getEmail() == email1) {
            pro1 = &(cur->data);
        }
        if ((cur->data).getEmail() == email2) {
            pro2 = &(cur->data);
        }
    }

    for (fr1 = (pro1->getFriends().getFirstNode()); fr1; fr1 = fr1->next) {
        for (fr2 = (pro2->getFriends().getFirstNode()); fr2; fr2 = fr2->next) {
            if (fr1->data == fr2->data) {
                common = (fr1->data);
                ret.insertAtTheTail(common);
            }
        }
    }

    return ret;


}

LinkedList<Post*> SocialNetwork::getListOfMostRecentPosts(const std::string& email, int k) {
    LinkedList<Post*> ret;
    Node<Profile>* current;
    Node<Post*>* fr1;
    Profile* pro;
    Post* imp;
    int i = 0;

    for (current = profiles.getFirstNode(); current; current = current->next) {
        if ((current->data).getEmail() == email) {
            pro = &(current->data);
        }
    }

    for (fr1 = (pro->getPosts().getLastNode()); i < k; ++i) {
        imp = fr1->data;
        ret.insertAtTheTail(imp);
        fr1 = fr1->prev;
    }
    return ret;

}

void SocialNetwork::print() const {
    std::cout << "# Printing the social network ..." << std::endl;

    std::cout << "# Number of profiles is " << profiles.getNumberOfNodes() << ":" << std::endl;
    profiles.print();

    std::cout << "# Number of posts is " << posts.getNumberOfNodes() << ":" << std::endl;
    posts.print();

    std::cout << "# Printing is done." << std::endl;
}
