#include "library.h"

int main()
{
    vector<LibraryItem*> items;

    //Loads existing data (if any)
    if (!loadData("library_data.txt", items))
    {
        cout << "No existing data, starting fresh." << endl;
    }

    int choice = 0;
    do
    {
        cout << "\nLibrary Menu:"            << endl;
        cout << "1. Display all items"      << endl;
        cout << "2. Add a Book"             << endl;
        cout << "3. Add a Magazine"         << endl;
        cout << "4. Borrow an item"         << endl;
        cout << "5. Return an item"         << endl;
        cout << "6. Search for an item"     << endl;
        cout << "0. Exit"                   << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
            case 1:
                //Displays items
                for (auto item : items)
                    item->displayInfo();
                break;

            case 2:
            {
                //Adds book
                Book* b = new Book();
                b->assignTitle();
                b->assignAuthor();
                b->assignID();
                b->assignGenre();
                items.push_back(b);
                saveData("library_data.txt", items);
                break;
            }

            case 3:
            {
                //Adds Magazine
                Magazine* m = new Magazine();
                m->assignTitle();
                m->assignAuthor();
                m->assignID();
                m->assignIssueNumber();
                items.push_back(m);
                saveData("library_data.txt", items);
                break;
            }

            case 4:
            {
                //Borrows Item
                cout << "Enter item ID to borrow: ";
                string id;
                getline(cin, id);

                bool found = false;
                for (auto item : items)
                {
                    if (item->getID() == id)
                    {
                        found = true;
                        if (!item->borrowItem())
                            cout << "That item is already borrowed." << endl;
                        else
                        {
                            cout << "Item borrowed successfully." << endl;
                            saveData("library_data.txt", items);
                        }
                        break;
                    }
                }
                if (!found)
                    cout << "No item with ID \"" << id << "\" found." << endl;
                break;
            }

            case 5:
            {
                // Returns item
                cout << "Enter item ID to return: ";
                string id;
                getline(cin, id);

                bool found = false;
                for (auto item : items)
                {
                    if (item->getID() == id)
                    {
                        found = true;
                        if (!item->returnItem())
                            cout << "That item was not borrowed." << endl;
                        else
                        {
                            cout << "Item returned successfully." << endl;
                            saveData("library_data.txt", items);
                        }
                        break;
                    }
                }
                if (!found)
                    cout << "No item with ID \"" << id << "\" found." << endl;
                break;
            }

            case 6:
            {
                //Searches item
                cout << "Enter item ID to search: ";
                string id;
                getline(cin, id);

                bool found = false;
                for (auto item : items)
                {
                    if (item->getID() == id)
                    {
                        found = true;
                        item->displayInfo();
                        break;
                    }
                }
                if (!found)
                    cout << "No item with ID \"" << id << "\" found." << endl;
                break;
            }

            case 0:
                //Exits program
                cout << "Exiting program." << endl;
                break;

            default:
                //Invalid choice
                cout << "Invalid choice." << endl;
                break;
        }
    }
    while (choice != 0);

    //saves .txt file with input
    saveData("library_data.txt", items);

    return 0;
}
