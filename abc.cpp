#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <conio.h>

using namespace std;

// Structure to represent a question
struct Question {
    string questionText;
    vector<string> options;
    char correctOption;
};

// Function to display a question and capture answer within a time limit
char askQuestionWithTimer(const Question &q, int timeLimitSeconds) {
    cout << q.questionText << endl;
    for (int i = 0; i < q.options.size(); i++) {
        cout << (char)('A' + i) << ". " << q.options[i] << endl;
    }

    cout << "\nYou have " << timeLimitSeconds << " seconds to answer...\n";
    char answer = ' ';
    bool answered = false;

    for (int i = 0; i < timeLimitSeconds * 10; i++) {
        if (_kbhit()) {
            answer = toupper(_getch());
            answered = true;
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    if (!answered) {
        cout << "\nTime's up! Moving to the next question.\n";
    }

    return answer;
}

int main() {
    vector<Question> quiz = {
        {"What is the capital of France?",
         {"Berlin", "Madrid", "Paris", "Rome"},
         'C'},
        {"Which planet is known as the Red Planet?",
         {"Earth", "Mars", "Jupiter", "Venus"},
         'B'},
        {"Who wrote 'Romeo and Juliet'?",
         {"Shakespeare", "Dickens", "Wordsworth", "Poe"},
         'A'},
        {"What is 9 x 9?",
         {"81", "72", "99", "108"},
         'A'}
    };

    int score = 0;
    int total = quiz.size();
    int timePerQuestion = 15; // seconds

    cout << "=====================================\n";
    cout << "      Welcome to the Quiz System     \n";
    cout << "=====================================\n";

    for (int i = 0; i < total; i++) {
        cout << "\nQuestion " << i + 1 << ":\n";
        char userAnswer = askQuestionWithTimer(quiz[i], timePerQuestion);

        if (userAnswer == quiz[i].correctOption) {
            cout << "✅ Correct!\n";
            score++;
        } else if (userAnswer != ' ') {
            cout << "❌ Wrong! Correct answer was: " << quiz[i].correctOption << "\n";
        }
    }

    cout << "\n=====================================\n";
    cout << "Quiz Over! Your Score: " << score << " out of " << total << endl;
    cout << "=====================================\n";

    return 0;
}
