#define CATCH_CONFIG_MAIN
#include <iostream>
#include <random>
#include <vector>
#include "catch_amalgamated.hpp"

std::vector<std::vector<int>> generateTestVec() {
    std::vector<std::vector<int>> vec(10, {0, 0});

    bool addNextNumber = true;
    srand(time(NULL));
    auto randomNum = 0;
    int indexOfVector{0};
    for (auto& it : vec) {
        int indexOfNum{0};
        bool addSecondNum{true};

        for (auto& iter : it) {
            randomNum = std::rand() % 11;
            if (indexOfNum == 0) {
                if (randomNum == 10) {
                    addSecondNum = false;
                }

                iter = randomNum;

            } else if (indexOfNum == 1) {
                if (!addSecondNum) {
                    iter = 0;
                } else {
                    while (!(randomNum + vec[indexOfVector][0] < 11)) {
                        randomNum = std::rand() % 11;
                    }
                    iter = randomNum;
                }
            }

            indexOfNum++;
        }
        indexOfVector++;
        addSecondNum = true;
    }
    return vec;
}

int countScore(const std::vector<std::vector<int>>& v) {
    int score = 0;
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            if(v.size() == 11 && i == 10 && v[i][0] == 10){
                score += 20;
                break;
            }
            else if (v[i][0] == 10 ) {
                if (i != 9) {
                    score += v[i][0] + v[i + 1][0] + v[i + 1][0];
                } else {
                    score += v[i][0];
                }
                break;
            } else if ((v[i][0] + v[i][1]) == 10 && (i != 10)) {
                if (i != 9) {
                    score += v[i][0] + v[i][1] + v[i + 1][0];
                } else {
                    score += v[i][0] + v[i][1];
                }

                break;
            } else {
                score += v[i][j];
            }
        }
    }
    return score;
}

SCENARIO("Ideal Game", "[idealGame]") {
    GIVEN("all pines missed") {
        std::vector<std::vector<int>> v(10, {0,0});
        int score = countScore(v);
        
        WHEN("expected score after game  should equal 0") {
            int expected = 0;
            THEN("score is equal 0") {
                REQUIRE(score == expected);
            }
        }
    }
    GIVEN("All the pines shot down first time in every round(Strike) ") {
      std::vector<std::vector<int>> v(11, {10,0});
        int score = countScore(v);
        std::cout << score << std::endl;
        WHEN("expected score after game should equal 300") {
            int expected = 300;
            THEN("Score is equal 300") {
                REQUIRE(score == expected);
            }
        }
    }
    GIVEN("All rounds results in Spare") {
        std::vector<std::vector<int>> v(11, {5,5});
        v[10][1] = 0;
        int score = countScore(v);

        WHEN("expected score after game should equal 150") {
            int expected = 150;
            THEN("Score is equal 150") {
                REQUIRE(score == expected);
            }
        }
    }
}

SCENARIO("Any given scenerio") {
    GIVEN("Vector of vectors with random numbers") {
        
        std::vector<std::vector<int>> vec = generateTestVec();
        int score = countScore(vec);

        WHEN("score is less than or equal to 300 and bigger or equal to 0 " << score) {
            REQUIRE(score <= 300);
            REQUIRE(score >= 0);
            THEN("number of rounds is less equal to 11 or 10") {   
             
                if(vec.size() == 10){
                        REQUIRE(vec.size() == 10);
                }else{
                        REQUIRE(vec.size() == 11);
                }
          
            }
        
        }
        WHEN("Given scores from each round ")
        {
            THEN("Scores from each round must be between 0 and 10")
            {
                
                for(auto& it : vec)
                {
                    REQUIRE(it[0] + it[1] > 0);
                    REQUIRE(it[0] + it[1] <= 10);
                }
            }

        }
        WHEN("Strike occured in 10th round"){
            THEN("Additional two throws are added"){
                if(vec[9][0] == 10)
                {
                    REQUIRE(vec[10][0]);
                    REQUIRE(vec[10][1]);
                    REQUIRE(vec.size() == 11);
                }

            }
        }
        WHEN("Spare occured in 10th round"){
            THEN("Additional one throw is added"){
                
                if(vec[9][0] != 10 && vec[9][0] + vec[9][1] == 10)
                {
                    REQUIRE(vec[10][0]);
                    REQUIRE(vec[10][1] == 0);
                    REQUIRE(vec.size() == 11);
                }
            }
        }
        WHEN("Spare or strike didn't occure in 10th round"){
            THEN("No additional rounds are added"){
                REQUIRE(vec.size() == 10);
            }
        }
       
    }
}
