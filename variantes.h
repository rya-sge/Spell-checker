//
// Created by micha on 2020-12-23.
//

#ifndef ASD2_LABS_2020_VARIANTES_H
#define ASD2_LABS_2020_VARIANTES_H

#include <vector>
#include <string>
#include <iostream>

class variantes {
private:
    std::string wordAOP;
    std::vector<std::string> tooManyChar;
    std::vector<std::string> tooFewChar;
    std::vector<std::string> wrongChar;
    std::vector<std::string> swapedChar;
public:
    variantes(std::string aop) {
        wordAOP = aop;
        tooMany();
        tooFew();
        wrong();
        swap();
    }

    const std::vector<std::string> &getTooManyChar() const {
        return tooManyChar;
    }

    const std::vector<std::string> &getTooFewChar() const {
        return tooFewChar;
    }

    const std::vector<std::string> &getWrongChar() const {
        return wrongChar;
    }

    const std::vector<std::string> &getSwapedChar() const {
        return swapedChar;
    }


    /**
     * HAVE TO BE DELETED
     */
    void displayDebug() {
        std::cout << "Too Many" << std::endl;
        vectorDisplay(tooManyChar);
        std::cout << "Too Few" << std::endl;
        vectorDisplay(tooFewChar);
        std::cout << "Wrong" << std::endl;
        vectorDisplay(wrongChar);
        std::cout << "Swap" << std::endl;
        vectorDisplay(swapedChar);
    }

private:
    void tooMany() {
        std::string var;
        for (size_t i = 0; i < wordAOP.length(); ++i) {
            var = wordAOP;
            var.erase(i, 1);
            tooManyChar.push_back(var);
        }
    }

    void tooFew() {
        std::string var;
        for (size_t i = 0; i <= wordAOP.length(); ++i) {
            for (int j = 0; j < 26; ++j) {
                var = wordAOP;
                var.insert(i, 1, char('a' + j));
                tooFewChar.push_back(var);
            }
        }
    }

    void wrong() {
        std::string var;
        for (size_t i = 0; i < wordAOP.length(); ++i) {
            for (int j = 0; j < 26; ++j) {
                var = wordAOP;
                var.replace(i, 1, 1, char('a' + j));
                wrongChar.push_back(var);
            }
        }
    }

    void swap() {
        std::string var;
        for (size_t i = 1; i < wordAOP.length(); ++i) {
            var = wordAOP;
            std::swap(var[i - 1], var[i]);
            swapedChar.push_back(var);
        }
    }

    /**
 * HAVE TO BE DELETED
 */
    void vectorDisplay(std::vector<std::string> var) {
        for (int i = 0; i < var.size(); ++i) {
            std::cout << var.at(i) << " " << std::endl;
        }
        std::cout << std::endl;
    }
};

#endif //ASD2_LABS_2020_VARIANTES_H

