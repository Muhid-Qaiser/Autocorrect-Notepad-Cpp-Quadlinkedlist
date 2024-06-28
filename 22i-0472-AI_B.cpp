#include <iostream>
#include <fstream>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#include <vector>
#include <sstream>
#include <cctype>
using namespace std;

vector<string> loadFromDictionary(const string filename)
{
    ifstream inputFile(filename);

    if (!inputFile.is_open())
    {
        cerr << "Error opening the file." << endl;
        // * Return an empty vector to indicate an error
        return vector<string>();
    }

    vector<string> words;
    string line;

    while (getline(inputFile, line))
    {
        istringstream iss(line);
        string word;

        while (iss >> word)
        {
            // * makes words lowercase
            for (char &c : word)
                if (isupper(c))
                    c = tolower(c);

            words.push_back(word);
        }
    }

    inputFile.close();

    // * return separated words by '\n'
    return words;
}

string swapAdjacentletters(string word, int index1)
{
    string result = "";

    for (int i = 0; i < word.length(); i++)
    {
        if (index1 == i)
        {
            // * swapping adjacent letters
            result += word[++i];
            result += word[i - 1];
        }

        else
            result += word[i];
    }
    return result;
}

class Node
{
public:
    char data;
    Node *up;
    Node *down;
    Node *left;
    Node *right;

    // * creating a new node
    Node(char d) : data(d)
    {
        up = NULL;
        down = NULL;
        left = NULL;
        right = NULL;
    }
};

class QuadLinkedList
{
    Node *head;
    Node *tail;
    Node *above;
    Node *front;
    Node *cursor;
    // Node *below;

public:
    QuadLinkedList() // * Constructor
    {
        head = NULL;
        tail = NULL;
        above = NULL;
        front = NULL;
        // below = NULL;

        cursor = new Node('|');
    }

    void insertInLine(char data) // * Insert data into line
    {
        Node *nn = new Node(data);

        // * if first node
        // if ((head == cursor && tail == cursor) || (head == NULL && tail == NULL))
        if ((head == NULL && tail == NULL) || head == tail)
        {
            head = nn;
            nn->right = cursor;
            cursor->left = nn;
            tail = cursor;

            if (tail->down)
            {
                Node *temp2 = head, *temp = tail->down;

                while (temp || temp2)
                {
                    if (temp)
                    {
                        temp->up = temp2;
                    }
                    if (temp2)
                    {
                        temp2->down = temp;
                    }

                    if (temp)
                        temp = temp->right;
                    if (temp2)
                        temp2 = temp2->right;
                }
            }
        }

        else // * Insert before cursor
        {
            // * creating proper links between the surrounding nodes
            above = tail->up;
            nn->left = tail->left;
            nn->right = tail;

            if (tail->left)
                tail->left->right = nn;

            tail->left = nn;
            nn->up = above;

            Node *temp = nn, *temp2 = tail->up;

            while (temp || temp2)
            {
                if (temp)
                {
                    temp->up = temp2;
                }
                if (temp2)
                {
                    temp2->down = temp;
                }

                if (temp)
                    temp = temp->right;
                if (temp2)
                    temp2 = temp2->right;
            }

            temp2 = nn;
            temp = tail->down;

            while (temp || temp2)
            {
                if (temp)
                {
                    temp->up = temp2;
                }
                if (temp2)
                {
                    temp2->down = temp;
                }

                if (temp)
                    temp = temp->right;
                if (temp2)
                    temp2 = temp2->right;
            }

            above = tail->up;

            // * retain head position
            if (tail->right == head)
            {
                head = tail->left;
            }
        }
    }

    void deleteLetter() // * Delete the letter
    {
        // if ((head == NULL && tail == NULL) || (head == cursor && tail == cursor) || tail->left == NULL)
        if ((head == NULL && tail == NULL) || (head == cursor && tail == cursor) || head == tail) // * if first node
        {
            return;
        }

        else if (tail->left) // * if not the left most node
        {
            Node *temp = tail, *temp2 = NULL, *temp3 = NULL;

            above = tail->up;

            if (tail->left->up)
                temp2 = tail->left->up;

            if (tail->left->down)
                temp3 = tail->left->down;

            Node *temp1 = tail->left;

            if (tail->left->left)
            {
                tail->left->left->right = tail;
            }
            tail->left = tail->left->left;
            temp1->left = NULL;
            temp1->right = NULL;
            temp1->up = NULL;
            temp1->down = NULL;

            if (head == temp1)
            {
                head = tail;
            }

            delete temp1;

            while (temp || temp2)
            {
                if (temp)
                {
                    temp->up = temp2;
                }
                if (temp2)
                {
                    temp2->down = temp;
                }

                if (temp)
                    temp = temp->right;
                if (temp2)
                    temp2 = temp2->right;
            }

            temp2 = tail;
            temp = temp3;

            while (temp || temp2)
            {
                if (temp)
                {
                    temp->up = temp2;
                }
                if (temp2)
                {
                    temp2->down = temp;
                }

                if (temp)
                    temp = temp->right;
                if (temp2)
                    temp2 = temp2->right;
            }
        }

        else if (!tail->left) // * if the left most node
        {
            Node *temp = tail->up, *temp3 = tail->down, *temp2 = tail->up, *end = NULL, *temp4 = NULL;
            above = tail->up;

            if (tail->up && tail->up->up)
                temp4 = tail->up->up;

            if (temp->right)
                while (temp->right->data != '\n' && temp->data != '\n' && temp->right != NULL)
                    temp = temp->right;
            else
                temp = NULL;

            tail->left = temp;

            end = tail;

            // while (end->right->data != '\n')
            // while (end->right != NULL && end->right->data != '\n')
            while (end->right != NULL)
            {
                end = end->right;
            }

            if (end->right)
            {
                Node *backslash = end->right;
                backslash->left = NULL;
                backslash->right = NULL;
                backslash->up = NULL;
                backslash->down = NULL;
                delete backslash;
                end->right = NULL;
            }

            if (temp)
            {
                if (temp->right)
                    if (!(end->data == '\n' && temp->right->data == '\n'))
                        end->right = temp->right;
            }

            if (temp)
                if (temp->right)
                    if (!(end->data == '\n' && temp->right->data == '\n'))
                        temp->right->left = end;

            // temp->right->left = tail;

            if (temp)
                temp->right = tail;

            temp = temp3;
            temp2 = tail;

            while (temp2->left != NULL)
                temp2 = temp2->left;
            temp3 = temp2;

            while (temp || temp2)
            {
                if (temp)
                {
                    temp->up = temp2;
                }
                if (temp2)
                {
                    temp2->down = temp;
                }

                if (temp)
                    temp = temp->right;
                if (temp2)
                    temp2 = temp2->right;
            }

            // if (tail->left && tail->left->up)
            // temp2 = tail->left->up->right;
            // temp2 = tail->up->up;

            temp2 = temp4;
            temp = temp3;

            while (temp || temp2)
            {
                if (temp)
                {
                    temp->up = temp2;
                }
                if (temp2)
                {
                    temp2->down = temp;
                }

                if (temp)
                    temp = temp->right;
                if (temp2)
                    temp2 = temp2->right;
            }

            // * shifting front and above ptr
            if (front)
                front = front->up;
            above = tail->up;
        }
    }

    void goToNextLine() // * Go to next line
    {
        Node *nn = new Node('\n');

        // if (tail == NULL && head == NULL || head == tail)
        if (tail == NULL && head == NULL) // * if first node
        {
            head = nn;

            // nn->right = cursor;
            // cursor->left = nn;
            nn->down = cursor;
            cursor->up = head;

            tail = cursor;
        }

        else if (head == tail) // * if first node
        {
            head = nn;
            nn->down = tail;
            tail->up = head;
        }

        else
        {
            if (!tail->left) // * if left most node
            {
                nn->up = front;
                front->down = nn;
            }
            else // * if not left most node
            {
                nn->left = tail->left;
                tail->left->right = nn;
            }
        }

        // * getting front node
        if (head->down == NULL)
        {
            front = head;
        }

        else
        {
            if (front && front->down)
                front = front->down;
            else if (front)
                front = front->down;
            else
                front = head;
        }

        above = front;

        Node *temp = NULL, *temp2 = NULL, *temp3 = NULL;

        // * creating links
        temp3 = tail;
        while (temp3->left != NULL)
        {
            temp3 = temp3->left;
        }

        temp3 = temp3->down;
        tail->left = NULL;

        // above = tail->up;

        temp2 = tail->up;
        temp = nn;

        while (temp || temp2)
        {
            if (temp)
            {
                temp->up = temp2;
            }
            if (temp2)
            {
                temp2->down = temp;
            }

            if (temp)
                temp = temp->right;
            if (temp2)
                temp2 = temp2->right;
        }

        temp2 = above;
        temp = tail;

        while (temp || temp2)
        {
            if (temp)
            {
                temp->up = temp2;
            }
            if (temp2)
            {
                temp2->down = temp;
            }

            if (temp)
                temp = temp->right;
            if (temp2)
                temp2 = temp2->right;
        }

        temp2 = tail;
        temp = temp3;

        while (temp || temp2)
        {
            if (temp)
            {
                temp->up = temp2;
            }
            if (temp2)
            {
                temp2->down = temp;
            }

            if (temp)
                temp = temp->right;
            if (temp2)
                temp2 = temp2->right;
        }

        above = tail->up;
    }

    void display() // * Display the Data Structure
    {
        Node *temp = head;
        Node *row = temp;

        // * displaying each row, node by node
        while (temp != NULL)
        {
            while (row != NULL)
            {
                cout << row->data;
                row = row->right;
            }
            temp = temp->down;
            row = temp;
        }
        cout << endl;
    }

    void moveCursor_Left() // * Move cursor to Left
    {
        if (head == NULL && tail == NULL || cursor->left == NULL || tail->left == NULL) // * if left most node
        {
            return;
        }

        else
        {

            above = tail->up;

            //* checking which nodes are not NULL to form links
            if (tail->up && tail->left->up)
            {
                above->down = tail->left;
                tail->left->up = above;
                above->left->down = tail;
                tail->up = above->left;
                above = above->left;
            }
            else if (!tail->up && tail->left->up)
            {
                tail->up = tail->left->up;
                tail->left->up->down = tail;
                tail->left->up = NULL;
            }

            if (tail->down && tail->left->down)
            {
                Node *temp = tail->down;
                tail->down = tail->left->down;
                tail->left->down->up = tail;
                tail->left->down = temp;
                temp->up = tail->left;
            }
            else if (!tail->down && tail->left->down)
            {
                tail->down = tail->left->down;
                tail->left->down->up = tail;
                tail->left->down = NULL;
            }

            Node *temp = tail->left;

            if (temp->left)
                temp->left->right = tail;
            tail->left = temp->left;

            temp->right = tail->right;
            if (tail->right)
                tail->right->left = temp;
            temp->left = tail;
            tail->right = temp;

            if (tail->right == head)
            {
                head = tail;
            }

            above = tail->up;
        }
    }

    void moveCursor_Right() // * Move cursor to Right
    {
        if (head == NULL && tail == NULL || cursor->right == NULL || tail->right == NULL || tail->right->data == '\n') // * if right most node
        {
            return;
        }

        else
        {
            //* checking which nodes are not NULL to form links

            if (tail->up && tail->right->up)
            {
                above->down = tail->right;
                tail->right->up = above;
                above->right->down = tail;
                tail->up = above->right;
                above = above->right;
            }
            else if (!tail->up && tail->right->up)
            {
                tail->up = tail->right->up;
                tail->right->up->down = tail;
                tail->right->up = NULL;
            }
            else if (!tail->right->up && tail->up)
            {
                tail->right->up = tail->up;
                tail->up->down = tail->right;
                tail->up = NULL;
            }

            if (tail->down && tail->right->down)
            {
                Node *temp = tail->down;
                tail->down = tail->right->down;
                tail->right->down->up = tail;
                tail->right->down = temp;
                temp->up = tail->right;
            }
            else if (!tail->down && tail->right->down)
            {
                tail->down = tail->right->down;
                tail->right->down->up = tail;
                tail->right->down = NULL;
            }
            else if (!tail->right->down && tail->down)
            {
                tail->right->down = tail->down;
                tail->down->up = tail->right;
                tail->down = NULL;
            }

            Node *temp = tail->right;

            if (temp->right)
                temp->right->left = tail;
            tail->right = temp->right;
            temp->left = tail->left;
            if (tail->left)
                tail->left->right = temp;
            temp->right = tail;
            tail->left = temp;

            if (tail->right == head)
            {
                head = tail;
            }
            else if (tail == head)
            {
                head = tail->left;
            }
        }
    }

    void moveCursor_Up() // * Move cursor to Up
    {
        if (head == NULL && tail == NULL || cursor->up == NULL || tail->up == NULL) // * if top most node
        {
            return;
        }

        else
        {

            //* checking which nodes are not NULL to form links

            if (tail->up->data != '\n')
            {
                Node *temp = NULL, *temp4 = tail->down;
                above = tail->up;
                // Node *t = tail->down;

                if (tail->left)
                    tail->left->right = tail->right;
                if (tail->right)
                    tail->right->left = tail->left;

                above->down = tail->right;
                if (tail->right)
                {
                    temp = tail->right;
                    tail->right->up = above;
                }
                tail->left = above;
                tail->right = above->right;
                if (above->right)
                    above->right->left = tail;
                above->right = tail;

                if (above->up && above->up->right)
                {
                    tail->up = above->up->right;
                    above->up->right->down = tail;
                    above = above->up->right;
                }
                else
                {
                    tail->up = NULL;
                    above = NULL;
                }

                front = front->up;

                Node *temp2 = temp, *temp3 = temp;
                temp = temp4;

                while (temp || temp2)
                {
                    if (temp)
                    {
                        temp->up = temp2;
                    }
                    if (temp2)
                    {
                        temp2->down = temp;
                    }

                    if (temp)
                        temp = temp->right;
                    if (temp2)
                        temp2 = temp2->right;
                }

                temp = temp3;
                temp2 = tail->left;
                // temp2 = above;

                while (temp || temp2)
                {
                    if (temp)
                    {
                        temp->up = temp2;
                    }
                    if (temp2)
                    {
                        temp2->down = temp;
                    }

                    if (temp)
                        temp = temp->right;
                    if (temp2)
                        temp2 = temp2->right;
                }

                temp = tail;
                temp2 = above;

                while (temp || temp2)
                {
                    if (temp)
                    {
                        temp->up = temp2;
                    }
                    if (temp2)
                    {
                        temp2->down = temp;
                    }

                    if (temp)
                        temp = temp->right;
                    if (temp2)
                        temp2 = temp2->right;
                }
            }

            else if (tail->up->data == '\n' && tail->up->left == NULL)
            {
                Node *temp2 = tail->right, *temp = tail->down, *temp3 = tail->right;

                above = tail->up;

                if (tail->right)
                    tail->right->left = tail->left;
                if (tail->left)
                    tail->left->right = tail->right;

                tail->right = tail->up;
                tail->up->left = tail;

                while (temp || temp2)
                {
                    if (temp)
                    {
                        temp->up = temp2;
                    }
                    if (temp2)
                    {
                        temp2->down = temp;
                    }

                    if (temp)
                        temp = temp->right;
                    if (temp2)
                        temp2 = temp2->right;
                }

                temp2 = tail;
                temp = temp3;

                while (temp || temp2)
                {
                    if (temp)
                    {
                        temp->up = temp2;
                    }
                    if (temp2)
                    {
                        temp2->down = temp;
                    }

                    if (temp)
                        temp = temp->right;
                    if (temp2)
                        temp2 = temp2->right;
                }

                temp = tail;

                if (above)
                    temp2 = above->up;
                // temp2 = temp4;

                while (temp || temp2)
                {
                    if (temp)
                    {
                        temp->up = temp2;
                    }
                    if (temp2)
                    {
                        temp2->down = temp;
                    }

                    if (temp)
                        temp = temp->right;
                    if (temp2)
                        temp2 = temp2->right;
                }

                front = tail->up;
                above = tail->up;
            }
        }
    }

    void moveCursor_Down() // * Move cursor to Down
    {
        if (head == NULL && tail == NULL || cursor->down == NULL || tail->down == NULL) // * if bottom most node
        {
            return;
        }

        else
        {
            if (head == tail)
                head = tail->right;

            above = tail->up;

            //* checking which nodes are not NULL to form links

            if (tail->down->data != '\n')
            {
                Node *temp = NULL;

                if (tail->left)
                    tail->left->right = tail->right;

                if (above)
                    above->down = tail->right;

                if (tail->right)
                {
                    temp = tail->right;
                    tail->right->left = tail->left;
                    tail->right->up = above;
                }
                tail->left = tail->down;
                tail->right = tail->down->right;

                if (tail->down->right)
                    tail->down->right->left = tail;

                tail->down->right = tail;

                if (tail->down->down && tail->down->down->right)
                {
                    tail->down->down->right->up = tail;
                    tail->down = tail->down->down->right;
                }
                else
                {
                    tail->down->up = NULL;
                    tail->down = NULL;
                }

                Node *temp2 = NULL, *temp3 = NULL, *temp4 = temp;

                // if (above && above->right)
                // temp2 = above->right;
                if (above)
                    temp2 = above;

                while (temp || temp2)
                {
                    if (temp)
                    {
                        temp->up = temp2;
                    }
                    if (temp2)
                    {
                        temp2->down = temp;
                    }

                    if (temp)
                        temp = temp->right;
                    if (temp2)
                        temp2 = temp2->right;
                }

                temp3 = temp4;
                temp = NULL;
                temp = tail->left;

                while (temp || temp3)
                {

                    if (temp)
                    {
                        temp->up = temp3;
                    }
                    if (temp3)
                    {
                        temp3->down = temp;
                    }

                    if (temp)
                        temp = temp->right;
                    if (temp3)
                        temp3 = temp3->right;
                }

                temp = tail->down;
                temp2 = tail;

                while (temp || temp2)
                {
                    if (temp)
                    {
                        temp->up = temp2;
                    }
                    if (temp2)
                    {
                        temp2->down = temp;
                    }

                    if (temp)
                        temp = temp->right;
                    if (temp2)
                        temp2 = temp2->right;
                }

                if (!front)
                    front = head;
                else
                    front = front->down;

                above = tail->up;
            }

            else if (tail->down->data == '\n' && tail->down->left == NULL)
            {
                Node *temp2 = tail->right, *temp = tail->up, *temp3 = tail->right;
                Node *temp4 = tail->down->down;

                // above = tail->up;

                if (tail->right)
                    tail->right->left = tail->left;
                if (tail->left)
                    tail->left->right = tail->right;

                tail->right = tail->down;
                tail->down->left = tail;

                while (temp || temp2)
                {
                    if (temp)
                    {
                        temp->down = temp2;
                    }
                    if (temp2)
                    {
                        temp2->up = temp;
                    }

                    if (temp)
                        temp = temp->right;
                    if (temp2)
                        temp2 = temp2->right;
                }

                temp2 = tail;
                temp = temp3;

                while (temp || temp2)
                {
                    if (temp)
                    {
                        temp->down = temp2;
                    }
                    if (temp2)
                    {
                        temp2->up = temp;
                    }

                    if (temp)
                        temp = temp->right;
                    if (temp2)
                        temp2 = temp2->right;
                }

                temp = tail;

                temp2 = temp4;

                while (temp || temp2)
                {
                    if (temp)
                    {
                        temp->down = temp2;
                    }
                    if (temp2)
                    {
                        temp2->up = temp;
                    }

                    if (temp)
                        temp = temp->right;
                    if (temp2)
                        temp2 = temp2->right;
                }

                front = tail->up;
                above = tail->up;
            }
        }
    }

    ~QuadLinkedList() // * Destructor
    {
        for (Node *line = head, *nextline = nullptr; line != nullptr; line = nextline)
        {
            Node *curr = line, *nextchar = nullptr;
            if (curr != nullptr)
                nextline = curr->down;
            for (; curr != nullptr; curr = nextchar)
            {
                nextchar = curr->right;
                if (curr->down != nullptr)
                    curr->down->up = nullptr;
                if (curr->up != nullptr)
                    curr->up->down = nullptr;
                if (curr->left != nullptr)
                    curr->left->right = nullptr;
                if (curr->right != nullptr)
                    curr->right->left = nullptr;
                delete curr;
            }
        }
        // head = tail = front = above = below = nullptr;
        head = tail = front = above = nullptr;
    }

    void saveToFile(const char *filename) // * Saving data of each node in a file
    {
        fstream file(filename, ios::out);
        for (Node *line = head; line != nullptr; line = line->down)
        {
            for (Node *curr = line; curr != nullptr; curr = curr->right)
                if (curr->data != '|')
                    file.write(&curr->data, sizeof(char));
        }
        file.close();
    }

    void loadFromFile(const char *filename) // * Loading data of each characrer from file into nodes
    {
        char curr;
        this->~QuadLinkedList();
        cursor = new Node('|');
        fstream file(filename, ios::in);
        while ((curr = file.get()) != EOF)
        {
            if (curr == '\n')
                this->goToNextLine();
            else
                this->insertInLine(curr);
        }
        file.close();
    }
};

bool checkInDictionary(string word, vector<string> dictionary)
{
    // * Checking if word exists in dictionary
    for (string &w : dictionary)
        if (w == word)
            return true;

    return false;
}

void spellChecker(string word, vector<string> dictionary)
{
    bool found = false;

    // * makes words lowercase
    for (char &c : word)
        if (isupper(c))
            c = tolower(c);

    found = checkInDictionary(word, dictionary);

    if (!found)
    {

        string correct_word;
        string alphabets = "abcdefghijklmnopqrstuvwxyz";
        int index;

        // * Substitution of a Letter
        {

            for (int i = 0; i < word.length(); i++)
            {
                correct_word = "";
                index = -1;

                for (int j = 0; j < word.length(); j++)
                    if (i != j)
                        correct_word += word[j];
                    else
                    {
                        index = j;
                        correct_word += '?';
                    }

                // if (index > 0)
                for (int j = 0; j < alphabets.length(); j++)
                {
                    correct_word[index] = alphabets[j];
                    found = checkInDictionary(correct_word, dictionary);

                    if (found)
                        break;
                }

                if (found)
                    break;
            }
        }

        // * Letter Omission
        if (!found)
        {
            for (int i = 0; i < word.length(); i++)
            {
                correct_word = "";

                for (int j = 0; j < word.length(); j++)
                    if (i != j)
                        correct_word += word[j];

                found = checkInDictionary(correct_word, dictionary);

                if (found)
                    break;
            }
        }

        // * Letter Insertion
        if (!found)
        {
            for (int i = 0; i < word.length() + 1; i++)
            {

                for (int j = 0; j < alphabets.length(); j++)
                {
                    correct_word = word;
                    correct_word.insert(i, 1, alphabets[j]);

                    found = checkInDictionary(correct_word, dictionary);

                    if (found)
                        break;
                }

                if (found)
                    break;
            }
        }

        // * Reversing Adjacent Letter
        if (!found)
        {
            for (int i = 0; i < word.length() - 1; i++)
            {
                correct_word = swapAdjacentletters(word, i);

                found = checkInDictionary(correct_word, dictionary);

                if (found)
                    break;
            }
        }

        if (!found)
            cout << "You are a Hopeless Speller!" << endl;
        else
            cout << word << " => " << correct_word << endl
                 << endl;
    }
}

int main()
{
    QuadLinkedList q1;
    vector<string> dictionary = loadFromDictionary("dictionary.txt"); // * Loading words from dictionary

    cout << "\n\n\n\t\tPress 'Esc' to exit.\n\n\n"
         << endl;

    char key;
    string curr, word;

    while (true)
    {
        key = _getch(); // * Use _getch() to read a character

        if (key == 27) // * Esc
        {
            system("cls");
            cout << "\n\n\n\t\tExited Successfully.\n\n\n"
                 << endl;
            break;
        }
        else if (key == 13) // * Enter
        {
            q1.goToNextLine();

            word = curr;
            curr = "";
        }
        else if (key == 8) // * Backspace
        {
            q1.deleteLetter();
            word = word.substr(0, word.length() - 1);
        }
        else if (key == 12) // * Ctrl+L
        {
            q1.loadFromFile("file.txt");
        }
        else if (key == 19) // * Ctrl+S
        {
            q1.saveToFile("file.txt");
        }
        else if (key == -32) // * Arrow keys
        {
            key = _getch();

            if (key == 75)
            {
                // * Left arrow
                q1.moveCursor_Left();
            }
            else if (key == 72)
            {
                // * Up arrow
                q1.moveCursor_Up();
            }
            else if (key == 77)
            {
                // * Right arrow
                q1.moveCursor_Right();
            }
            else if (key == 80)
            {
                // * Down arrow
                q1.moveCursor_Down();
            }
        }
        else
        {
            // * Characters
            q1.insertInLine(key);

            if (key != ' ')
                curr += key;
            else
            {
                word = curr;
                curr = "";
            }
        }

        // * Refresh Console
        system("cls");
        q1.display();

        // * Partitioning the Console
        for (int i = 0; i < 8; i++)
            cout << "\n";

        cout << "-------------------------------------------------------------\n\n";
        if (word != "")
            spellChecker(word, dictionary); // * Suggestions of words
    }

    return 0;
}
