/*
    DEFENCE FORCES APPLICATION ASSISTANT
    CLI Based Offline Chatbot
    Language : C++
*/

#include <iostream>
#include <string>

using namespace std;

class DefenceAssistant
{
private:
    string name;
    int age;
    int qualificationChoice;
    double percentage;

public:
    void welcome()
    {
        cout << "\n=====================================================\n";
        cout << "        DEFENCE FORCES APPLICATION ASSISTANT\n";
        cout << "=====================================================\n";
    }

    void createProfile()
    {
        cout << "\nEnter Candidate Name : ";
        getline(cin, name);

        cout << "Enter Age : ";
        cin >> age;

        cout << "\nSelect Qualification\n";

        cout << "1. 12th PCM\n";
        cout << "2. 12th Non-PCM\n";
        cout << "3. Diploma\n";
        cout << "4. BTech / Engineering\n";
        cout << "5. BSc\n";
        cout << "6. BA\n";
        cout << "7. BCom\n";
        cout << "8. Post Graduation\n";
        cout << "9. Other\n";

        cout << "\nEnter Choice : ";
        cin >> qualificationChoice;

        if (qualificationChoice == 9)
        {
            string otherQualification;

            cin.ignore();

            cout << "Enter Qualification : ";
            getline(cin, otherQualification);

            cout << "Qualification Recorded : "
                 << otherQualification << endl;
        }

        cout << "Enter Percentage : ";
        cin >> percentage;

        cout << "\nProfile Created Successfully.\n";
    }

    void eligibilityCheck()
    {
        cout << "\n========== ELIGIBILITY RESULT ==========\n";

        if (age >= 16 && age <= 24)
        {
            cout << "Age Status : Eligible for multiple entries.\n";
        }
        else
        {
            cout << "Age Status : Limited opportunities available.\n";
        }

        switch (qualificationChoice)
        {
        case 1:
            cout << "Recommended Entries : NDA, Technical Entries\n";
            break;

        case 2:
            cout << "Recommended Entries : Non-Technical Entries\n";
            break;

        case 3:
            cout << "Recommended Entries : Technical Trades\n";
            break;

        case 4:
            cout << "Recommended Entries : AFCAT, CDS, Technical Branches\n";
            break;

        case 5:
            cout << "Recommended Entries : AFCAT, CDS\n";
            break;

        case 6:
        case 7:
            cout << "Recommended Entries : CDS, Administration Branches\n";
            break;

        case 8:
            cout << "Recommended Entries : Advanced Officer Entries\n";
            break;

        default:
            cout << "Please verify official eligibility criteria.\n";
        }

        if (percentage >= 60)
        {
            cout << "Academic Performance : Good\n";
        }
        else
        {
            cout << "Academic Performance : Needs Improvement\n";
        }
    }

    void entrySchemes()
    {
        int choice;

        cout << "\n========== ENTRY SCHEMES ==========\n";

        cout << "1. NDA\n";
        cout << "2. CDS\n";
        cout << "3. AFCAT\n";
        cout << "4. Agniveer\n";
        cout << "5. Technical Entry\n";
        cout << "6. Back\n";

        cout << "\nEnter Choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "\nNDA:\n";
            cout << "- After 12th PCM\n";
            cout << "- Written Exam + SSB\n";
            break;

        case 2:
            cout << "\nCDS:\n";
            cout << "- Graduation Required\n";
            cout << "- UPSC Conducted\n";
            break;

        case 3:
            cout << "\nAFCAT:\n";
            cout << "- Graduate Entry\n";
            cout << "- Flying / Technical / Ground Duty\n";
            break;

        case 4:
            cout << "\nAgniveer:\n";
            cout << "- Short Service Entry\n";
            break;

        case 5:
            cout << "\nTechnical Entry:\n";
            cout << "- Engineering Background Preferred\n";
            break;

        default:
            cout << "\nReturning To Main Menu.\n";
        }
    }

    void physicalStandards()
    {
        int choice;

        cout << "\n========== PHYSICAL STANDARDS ==========\n";

        cout << "1. Running Standards\n";
        cout << "2. Pushups Standards\n";
        cout << "3. Vision Standards\n";
        cout << "4. Fitness Tips\n";
        cout << "5. Back\n";

        cout << "\nEnter Choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "\nTarget : 1.6 km under 6-7 minutes\n";
            break;

        case 2:
            cout << "\nTarget : 40+ Pushups Recommended\n";
            break;

        case 3:
            cout << "\nGood eyesight required for most entries.\n";
            break;

        case 4:
            cout << "\nConsistency beats motivation.\n";
            break;

        default:
            cout << "\nReturning To Main Menu.\n";
        }
    }

    void ssbGuidance()
    {
        int choice;

        cout << "\n========== SSB GUIDANCE ==========\n";

        cout << "1. OLQs\n";
        cout << "2. Psychology Tests\n";
        cout << "3. Group Discussion\n";
        cout << "4. Interview Tips\n";
        cout << "5. Back\n";

        cout << "\nEnter Choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "\nOLQs = Leadership, Confidence, Responsibility\n";
            break;

        case 2:
            cout << "\nPsychology tests evaluate natural thinking.\n";
            break;

        case 3:
            cout << "\nSpeak clearly and logically.\n";
            break;

        case 4:
            cout << "\nAvoid fake personality projection.\n";
            break;

        default:
            cout << "\nReturning To Main Menu.\n";
        }
    }

    void documentsRequired()
    {
        cout << "\n========== REQUIRED DOCUMENTS ==========\n";

        cout << "1. Aadhaar Card\n";
        cout << "2. 10th Marksheet\n";
        cout << "3. 12th Marksheet\n";
        cout << "4. Graduation Certificates\n";
        cout << "5. Passport Photos\n";
        cout << "6. NCC Certificate (Optional)\n";
    }

    void preparationTips()
    {
        int choice;

        cout << "\n========== PREPARATION TIPS ==========\n";

        cout << "1. Mathematics\n";
        cout << "2. English\n";
        cout << "3. Current Affairs\n";
        cout << "4. Mock Tests\n";
        cout << "5. Time Management\n";
        cout << "6. Back\n";

        cout << "\nEnter Choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "\nSolve maths daily.\n";
            break;

        case 2:
            cout << "\nImprove vocabulary and comprehension.\n";
            break;

        case 3:
            cout << "\nRead defence and national news daily.\n";
            break;

        case 4:
            cout << "\nWeekly mock tests are essential.\n";
            break;

        case 5:
            cout << "\nDiscipline > Motivation.\n";
            break;

        default:
            cout << "\nReturning To Main Menu.\n";
        }
    }

    void quickQueryMode()
    {
        int choice;

        cout << "\n========== QUICK QUERY MODE ==========\n";

        cout << "1. NDA Eligibility\n";
        cout << "2. AFCAT Eligibility\n";
        cout << "3. SSB Tips\n";
        cout << "4. Fitness Advice\n";
        cout << "5. Documents Required\n";
        cout << "6. Motivation\n";
        cout << "7. Other Query\n";
        cout << "8. Exit Query Mode\n";

        cout << "\nEnter Choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "\nNDA requires 12th PCM qualification.\n";
            break;

        case 2:
            cout << "\nAFCAT requires graduation.\n";
            break;

        case 3:
            cout << "\nNatural confidence matters more than memorized answers.\n";
            break;

        case 4:
            cout << "\nDaily running and strength training are essential.\n";
            break;

        case 5:
            cout << "\nEducational and identity documents are mandatory.\n";
            break;

        case 6:
            cout << "\nAverage effort gives average results.\n";
            break;

        case 7:
        {
            string query;

            cin.ignore();

            cout << "\nEnter Your Query : ";
            getline(cin, query);

            cout << "\nAssistant Response:\n";
            cout << "Your query has been recorded.\n";
            cout << "Advanced NLP is not implemented currently.\n";

            break;
        }

        default:
            cout << "\nExiting Query Mode.\n";
        }
    }

    void start()
    {
        int choice;

        welcome();

        createProfile();

        while (true)
        {
            cout << "\n=====================================================\n";

            cout << "\nMAIN MENU\n";

            cout << "1. Eligibility Check\n";
            cout << "2. Entry Schemes\n";
            cout << "3. Physical Standards\n";
            cout << "4. SSB Guidance\n";
            cout << "5. Documents Required\n";
            cout << "6. Preparation Tips\n";
            cout << "7. Quick Query Mode\n";
            cout << "8. Exit\n";

            cout << "\nEnter Choice : ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                eligibilityCheck();
                break;

            case 2:
                entrySchemes();
                break;

            case 3:
                physicalStandards();
                break;

            case 4:
                ssbGuidance();
                break;

            case 5:
                documentsRequired();
                break;

            case 6:
                preparationTips();
                break;

            case 7:
                quickQueryMode();
                break;

            case 8:
                cout << "\nThank You Candidate.\n";
                cout << "Best Wishes For Defence Services Preparation.\n";
                return;

            default:
                cout << "\nInvalid Choice.\n";
            }
        }
    }
};

int main()
{
    DefenceAssistant bot;

    bot.start();

    return 0;
}