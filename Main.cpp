#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <fstream>
#include<cstdlib>
#include <bits/stdc++.h>
using namespace std;
class TrieNode
{

    public:
        char data;
        TrieNode **children;
        bool isTerminal;

        TrieNode(char data)
        {
            this->data = data;
            children = new TrieNode *[26];
            for (int i = 0; i < 26; i++)
            {
                children[i] = NULL;
            }
            isTerminal = false;
        }
};

class Trie
{

    TrieNode *root;

    public:
        int count;

        Trie()
        {
            this->count = 0;
            root = new TrieNode('\0');
        }

        bool insertWord(TrieNode *root, string word)
        {

            if (word.size() == 0)
            {
                if (!root->isTerminal)
                {
                    root->isTerminal = true;
                    return true;
                }
                else
                {
                    return false;
                }
            }
            int index = word[0] - 'a';
            TrieNode *child;

            if (root->children[index] != NULL)
            {
                child = root->children[index];
            }
            else
            {
                child = new TrieNode(word[0]);
                root->children[index] = child;
            }

            return insertWord(child, word.substr(1));
        }

        void insertWord(string word)
        {
            if (insertWord(root, word))
            {
                this->count++;
            }
        }

        void possibleWord(TrieNode *root, string ans, string pattern)
        {

            if (!pattern.size() && root->isTerminal == true)
            {
                cout << ans << endl;
            }

            if (pattern.size())
            {
                int index = pattern[0] - 'a';
                if (root->children[index] == NULL)
                {
                    return;
                }
                else
                {
                    ans += pattern[0];
                    possibleWord(root->children[index], ans, pattern.substr(1));
                }
            }
            else
            {
                for (int i = 0; i < 26; i++)
                {
                    if (root->children[i] != NULL)
                    {
                        string smallAns = ans;
                        smallAns += root->children[i]->data;
                        possibleWord(root->children[i], smallAns, pattern);
                    }
                }
            }
        }

        TrieNode *findWord(TrieNode *root, string pattern)
        {

            if (pattern.size() == 0)
            {
                return root;
            }

            int index = pattern[0] - 'a';
            TrieNode *child;

            if (root->children[index] != NULL)
            {
                child = root->children[index];
                return findWord(child, pattern.substr(1));
            }
            else
            {
                return NULL;
            }
        }

        void autoComplete(vector<string> input, string pattern)
        {

            for (int i = 0; i < input.size(); i++)
            {
                insertWord(input[i]);
            }

            string ans = "";

            possibleWord(root, ans, pattern);
        }
};

int main()
{
    Trie t;
    stack <string > recent;
    vector <string > tempstack;
    string word;
    string word1;
    string pattern;
    vector<string> vect;
    int k;
    while (1)
    {
        system("cls");
        cout << "1.Enter words from Saved file " << endl;
        cout << "2.Enter new words " << endl;
        cout << "3.Auto suggestion tab " << endl;
        cout << "4.Import previous searches for Auto suggest  " << endl;
        cout << "5.User Searched Words " << endl;
        cout << "6.Exit " << endl;
        cout << "Enter your Choice" << endl;
        cin >> k;
        switch (k)
        {
            case 1:
            {
                system("cls");
                ifstream infile;
                ofstream ofile;
                string filename;
                cout << "Enter Name of file you want to enter" << endl;
                cin >> filename;
                filename += ".txt";
                infile.open(filename.c_str(), ios::app);
                ofile.open("words.txt", ios::app);
                int count = 0;
                string wordcount;
                while (infile >> wordcount)
                {
                    ++count;
                }
                if(count==0)
                {
                    cout<< "Your file has " << count << " words, kindly enter words in your file."<<endl;
                }
                else
                {
                    cout << "Your file has " << count << " words ,how many do you want to import ?";
                    int N;
                    cin >> N;
                    infile.close();
                    infile.open(filename.c_str(), ios::app);
                    string word;
                    for (int i = 0; i < N; i++)
                    {
                        int r = (rand() % count) + 1;
                        int j=0;
                        for(;j<=r;j++)
                        {
                            infile >> word;

                        }
                        transform(word.begin(), word.end(), word.begin(), ::tolower);
                        cout<<word<<endl;
                        ofile << word << endl;
                    }
                    cout << "Words displayed Successfully."<<endl;
                }
                cout << "Press Any Key To Continue!!"<<endl;
                _getch();
                ofile.close();
                infile.close();
                break;
            }
            case 2:
            {
                system("cls");
                ofstream ofile;
                ofile.open("words.txt", ios::app);
                int N;
                cout << "Enter number of words you want to enter"<<endl;
                cin >> N;
                cout << "Enter words"<<endl;
                for (int i = 0; i < N; i++)
                {
                    cin >> word;
                    transform(word.begin(), word.end(), word.begin(), ::tolower);
                    ofile << word << endl;
                }
                cout << "Words Entered Successfully"<<endl;
                cout << "Press Any Key To Continue"<<endl;
                _getch();
                ofile.close();
                break;
            }
            case 3:
            {
                system("cls");
                ifstream ifile;
                ifile.open("words.txt", ios::in);
                string username;
                cout<<"Enter your Username ";cin>>username;cout<<endl;
                username+=".txt";
                cout << " Enter Pattern ";
                cin >> pattern;
                transform(pattern.begin(), pattern.end(), pattern.begin(), ::tolower);
                ofstream ofile;
                ofile.open(username.c_str(),ios::app);
                while (ifile >> word1)
                {
                    transform(word1.begin(), word1.end(), word1.begin(), ::tolower);
                    vect.push_back(word1);
                }
                ifile.close();
                t.autoComplete(vect, pattern);
                recent.push(pattern);
                string ans;
                cout<<"Did you find your word ? y/n"<<endl;
                cin>>ans;
                if(ans=="n")
                {
                    string newword;
                    cout<<"Enter the word you were looking for "<<endl;
                    cin>>newword;
                    ifstream ifile;
                    ifile.open("words.txt",ios::in);
                    bool flag=false;
                    string checkstr;
                    while(ifile>>checkstr)
                    {
                        if(checkstr==newword)
                        {
                            flag=true;
                            break;
                        }
                    }
                    if(flag)
                    {
                        cout<<"You Entered "<<newword<<" which is already present."<<endl;
                    }
                    else
                    {
                        cout<<"Your word was saved . Thank you "<<endl;
                        recent.push(newword);
                        transform(newword.begin(), newword.end(), newword.begin(), ::tolower);
                        ofile<<newword<<endl;
                    }
                }
                ofile.close();
                ifile.close();
                cout << " Press any key to continue "<<endl;
                _getch();
                break;
            }
            case 4:
            {
                system("cls");
                ifstream infile;
                ofstream ofile;
                string filename;
                cout << "Enter Username " << endl;
                cin >> filename;
                string na=filename;
                filename += ".txt";
                infile.open(filename.c_str(), ios::app);
                ofile.open("words.txt", ios::app);
                int count = 0;
                string wordcount;
                while (infile >> wordcount)
                {
                    ++count;
                }
                cout << " Hi ,"<<na << " you have "<<count<<" search record, how many do you want to add to Autosuggest? "<<endl;
                int N;
                cin >> N;
                infile.close();
                infile.open(filename.c_str(), ios::app);
                string word;
                for (int i = 0; i < N; i++)
                {
                    infile >> word;
                    cout << word<<endl;
                    ofile << word << endl;
                }
                cout << "Words Entered Successfully"<<endl;
                cout << "Press Any Key To Continue"<<endl;
                _getch();
                ofile.close();
                infile.close();
                break;
            }
            case 5:
            {
                cout<<"List of words searched by ALL Users "<<endl;
                while(!recent.empty())
                {
                    string temp=recent.top();
                    tempstack.push_back(temp);
                    recent.pop();
                    cout<<temp<<endl;
                }
                for(int i=0;i<tempstack.size();i++)
                {
                    recent.push(tempstack[i]);
                }
                cout << "Press Any Key To Continue"<<endl;
                _getch();
                break;
            }
            case 6:
            {
                exit(0);
                break;
            }
            default:
            {
                cout << "Invalid choice"<<endl;
                break;
            }
        }
    }
}
