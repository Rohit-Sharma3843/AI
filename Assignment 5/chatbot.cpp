#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <limits>

using namespace std;

// ─── Utilities ────────────────────────────────────────────────────────────────

string toLower(string s)
{
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

bool contains(const string &text, const string &keyword)
{
    return toLower(text).find(toLower(keyword)) != string::npos;
}

bool containsAny(const string &text, const vector<string> &keywords)
{
    for (const auto &kw : keywords)
    {
        if (contains(text, kw))
            return true;
    }
    return false;
}

string timestamp()
{
    time_t t = time(nullptr);
    tm *tmNow = localtime(&t);
    char buf[9];
    strftime(buf, sizeof(buf), "%H:%M:%S", tmNow);
    return string(buf);
}

// ─── Display Helpers ──────────────────────────────────────────────────────────

void printDivider(bool heavy = false)
{
    string line = heavy ? string(60, '=') : string(60, '-');
    cout << line << "\n";
}

void printBot(const string &msg)
{
    cout << "\n  \033[36m[BOT " << timestamp() << "]\033[0m  " << msg << "\n\n";
}

void printUser(const string &msg)
{
    cout << "  \033[33m[YOU " << timestamp() << "]\033[0m  " << msg << "\n";
}

void printInfo(const string &msg)
{
    cout << "  \033[90m" << msg << "\033[0m\n";
}

void printMenu(const vector<string> &options)
{
    for (size_t i = 0; i < options.size(); i++)
    {
        cout << "    \033[32m[" << (i + 1) << "]\033[0m " << options[i] << "\n";
    }
    cout << "\n";
}

// ─── Session State ────────────────────────────────────────────────────────────

struct Session
{
    string customerName;
    string ticketId;
    string topic;
    bool resolved = false;
    bool escalated = false;
    int turnCount = 0;

    string generateTicket()
    {
        srand((unsigned)time(nullptr) + turnCount);
        return "TKT-" + to_string(1000 + rand() % 9000);
    }
};

struct FAQ
{
    vector<string> triggers;
    string answer;
};

const vector<FAQ> FAQS = {
    {{"refund", "money back", "return", "reimburse"},
     "Our refund policy allows returns within 30 days of purchase.\n"
     "    To initiate a refund:\n"
     "      1. Visit our website ->Orders ->Request Refund\n"
     "      2. Select the item and reason\n"
     "      3. Refunds are processed within 5->7 business days."},
    {{"shipping", "delivery", "tracking", "package", "arrive", "dispatch"},
     "Shipping details:\n"
     "      -> Standard delivery: 5->7 business days\n"
     "      -> Express delivery:  2->3 business days\n"
     "      -> Same-day:          available in select cities\n"
     "    Track your order at: website ->My Orders ->Track Package."},
    {{"password", "login", "sign in", "account", "forgot", "reset"},
     "To reset your password:\n"
     "      1. Go to the login page and click 'Forgot Password'\n"
     "      2. Enter your registered email address\n"
     "      3. Check your inbox for the reset link (valid for 15 min)\n"
     "    If you're still locked out, I can escalate to our auth team."},
    {{"cancel", "cancellation", "unsubscribe", "stop subscription"},
     "To cancel your subscription or order:\n"
     "      -> Orders (not yet shipped): go to My Orders ->Cancel\n"
     "      -> Subscription: go to Account ->Subscription ->Cancel Plan\n"
     "      -> Shipped orders must be returned for a refund."},
    {{"payment", "billing", "invoice", "charge", "credit card", "upi", "pay"},
     "We accept: Credit/Debit cards, UPI, Net Banking, Wallets.\n"
     "    For billing queries:\n"
     "      -> Duplicate charge?  ->screenshot + order ID helps us resolve it fast\n"
     "      -> Invoice copy?       ->Account ->Orders ->Download Invoice"},
    {{"warranty", "guarantee", "broken", "defective", "damaged", "repair"},
     "Warranty coverage:\n"
     "      -> Electronics: 1-year manufacturer warranty\n"
     "      -> Appliances:  2-year warranty\n"
     "    For defective items received, we offer free replacement within 7 days.\n"
     "    Please keep the original packaging for warranty claims."},
    {{"offer", "discount", "coupon", "promo", "deal", "sale"},
     "Current promotions:\n"
     "      -> Use code WELCOME10 for 10% off your first order\n"
     "      -> Weekend Sale — up to 40% off selected categories\n"
     "      -> Refer a friend and earn ₹200 wallet credit\n"
     "    Check the 'Offers' section on our website for the latest deals."},
    {{"contact", "phone", "email", "reach", "speak", "human", "agent", "representative"},
     "You can reach our support team via:\n"
     "      -> Phone:    1800-XXX-XXXX (Mon->Sat, 9 AM -> 6 PM)\n"
     "      -> Email:    support@company.com (reply within 24 hours)\n"
     "      -> Live Chat: available on our website\n"
     "    Type 'escalate' at any time and I'll flag your case for a human agent."},
    {{"hour", "timing", "open", "available", "working hours"},
     "Our support is available:\n"
     "      -> Chatbot (me!):  24 X 7\n"
     "      -> Phone support:  Mon->Sat, 9 AM -> 6 PM IST\n"
     "      -> Email support:  24 hrs response time"},
};

string findAnswer(const string &input)
{
    for (const auto &faq : FAQS)
    {
        if (containsAny(input, faq.triggers))
        {
            return faq.answer;
        }
    }
    return "";
}

class CustomerBot
{
    Session session;

    void greet()
    {
        printDivider(true);
        cout << "\n"
             << "   \033[36m╔══════════════════════════════════════╗\033[0m\n"
             << "   \033[36m║   ShopEase Customer Support Bot 🤖  ║\033[0m\n"
             << "   \033[36m╚══════════════════════════════════════╝\033[0m\n\n";
        printDivider(false);
        printInfo("  Type your question naturally, or choose a topic.");
        printInfo("  Commands: 'menu' | 'ticket' | 'escalate' | 'quit'");
        printDivider(false);

        printBot("Hello! Welcome to ShopEase Support. I'm here to help you.\n"
                 "    May I know your name?");
    }

    void askName()
    {
        string input;
        getline(cin, input);
        if (input.empty())
            input = "Valued Customer";
        session.customerName = input;
        printUser(input);
        session.ticketId = session.generateTicket();
        printBot("Nice to meet you, \033[1m" + session.customerName + "\033[0m!\n"
                                                                      "    Your session ticket is: \033[33m" +
                 session.ticketId + "\033[0m\n\n"
                                    "    How can I assist you today? You can ask about:\n");
        showTopicMenu();
    }

    void showTopicMenu()
    {
        printMenu({"Refunds & Returns",
                   "Shipping & Tracking",
                   "Account & Password",
                   "Payments & Billing",
                   "Warranty & Defects",
                   "Offers & Discounts",
                   "Contact Information",
                   "Something else (just type your question)"});
    }

    bool handleCommand(const string &input)
    {
        string low = toLower(input);

        if (low == "quit" || low == "exit" || low == "bye" || low == "q")
        {
            farewell();
            return true;
        }
        if (low == "menu")
        {
            printBot("Sure! Here are the topics I can help with:");
            showTopicMenu();
            return true;
        }
        if (low == "ticket")
        {
            printBot("Your current ticket ID is: \033[33m" + session.ticketId + "\033[0m\n"
                                                                                "    Save this for any follow-up queries.");
            return true;
        }
        if (contains(low, "escalate") || contains(low, "human") || contains(low, "agent"))
        {
            escalate();
            return true;
        }
        if (low == "resolved" || low == "done" || low == "thanks" ||
            low == "thank you" || low == "ok thanks" ||
            low == "yes" || low == "yeah" || low == "yep" || low == "yup" || low == "ok")
        {
            printBot("Great, glad I could help!\n"
                     "    Is there anything else I can assist you with?");
            return true;
        }
        if (low == "no" || low == "nope" || low == "not really" || low == "no thanks")
        {
            printBot("I\'m sorry I couldn\'t fully help. You can:\n"
                     "      - Rephrase your question and try again\n"
                     "      - Type \'menu\' to browse all topics\n"
                     "      - Type \'escalate\' to speak with a human agent");
            return true;
        }
        if (low.size() == 1 && low[0] >= '1' && low[0] <= '8')
        {
            handleMenuChoice(low[0] - '0');
            return true;
        }
        return false;
    }

    void handleMenuChoice(int choice)
    {
        const vector<string> queries = {
            "refund", "shipping", "password", "payment",
            "warranty", "offer", "contact", ""};
        if (choice >= 1 && choice <= 7)
        {
            string answer = findAnswer(queries[choice - 1]);
            printBot(answer);
            printBot("Did that answer your question? (yes / no / anything else)");
        }
        else
        {
            printBot("Of course! Go ahead and describe your issue — I'm listening.");
        }
    }

    void escalate()
    {
        session.escalated = true;
        printBot("Understood. I'll escalate your case to a human agent.\n\n"
                 "    \033[33mEscalation Summary\033[0m\n"
                 "    ─────────────────────────────────────\n"
                 "    Customer : " +
                 session.customerName + "\n"
                                        "    Ticket   : " +
                 session.ticketId + "\n"
                                    "    Topic    : " +
                 (session.topic.empty() ? "General Inquiry" : session.topic) + "\n"
                                                                               "    Turns    : " +
                 to_string(session.turnCount) + "\n"
                                                "    ─────────────────────────────────────\n\n"
                                                "    An agent will contact you within 2 hours during business hours.\n"
                                                "    Keep your ticket ID \033[33m" +
                 session.ticketId + "\033[0m handy.");
    }

    void farewell()
    {
        printDivider(false);
        printBot("Thank you for contacting ShopEase, \033[1m" + session.customerName + "\033[0m!\n"
                                                                                       "    Your ticket \033[33m" +
                 session.ticketId + "\033[0m has been saved.\n\n"
                                    "    Have a wonderful day! 👋");
        printDivider(true);
    }

    void handleInput(const string &input)
    {
        session.turnCount++;
        string answer = findAnswer(input);
        if (!answer.empty())
        {
            for (const auto &faq : FAQS)
            {
                if (containsAny(input, faq.triggers))
                {
                    session.topic = faq.triggers[0];
                    break;
                }
            }
            printBot(answer + "\n\n    Anything else I can help you with?");
        }
        else
        {
            printBot("I'm sorry, I didn't quite catch that. Let me suggest a few options:\n");
            showTopicMenu();
            printInfo("  Or type 'escalate' to speak with a human agent.");
        }
    }

public:
    void run()
    {
        greet();
        askName();

        string input;
        while (true)
        {
            getline(cin, input);

            if (input.empty())
                continue;
            printUser(input);

            if (handleCommand(input))
            {
                string low = toLower(input);
                if (low == "quit" || low == "exit" || low == "bye" || low == "q")
                    break;
                if (session.escalated)
                    break;
            }
            else
            {
                handleInput(input);
            }
        }
    }
};

int main()
{

    CustomerBot bot;
    bot.run();
    return 0;
}