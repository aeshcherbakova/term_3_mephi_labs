#include "dialog.h"

namespace Prog3C {

    void set_train(train& main_train) {
        std::cout << "Train parameters: ";
        try {
            std::cin >> main_train;
        }
        catch (const std::invalid_argument& error) {
            std::cerr << "Error: " << error.what() << std::endl;
        }
    }


    int occupy_seats(train& main_train, int pass_num) {
        int carriage_index;
        if (!getNum(carriage_index, "Input carriage number: ")) return 0;
        if (!pass_num) 
            if (!getNum(pass_num, "Input number of passengers: ")) return 0;

        try {
            main_train(carriage_index, pass_num);
        }
        catch (const std::invalid_argument& error) {
            std::cout << "Error: " << error.what() << std::endl;
            return -1;
        }
        return 1;
    }


    // функция ввода кол-ва пассажиров (возвр 1, если успешно, и 0, если конец файла)
    int input_num_of_pass(int& num, int upper_border) {
        std::cout << "Input number of passengers that you want to add: ";
        while (1) {
            if (!getNum(num, "")) return 0;
            if (num < 1 || num > upper_border)
                std::cout << "Invalid number of passengers!" << std::endl;
            else return 1;
        }
    }

    void get_train_occupancy_information(train& main_train) {
        std::cout << std::endl << "Your train info:" << std::endl << main_train << std::endl;
    }

    // если поезд заполнен, спрашиваем, что делать дальше
    int train_is_full(train& tr) {
        std::cout << "This train is full" << std::endl;
        std::cout <<
            "0. Quit" << std::endl <<
            "1. Create a new train" << std::endl <<
            "2. Add carriages to this train" << std::endl;
        int answer;
        struct carriage* cars = new carriage[1];
        while (1) {
            if (!getNum(answer, "")) return 0;
            switch (answer) {
            case 0:
                return 0;
            case 1:
                tr.set_carriages(cars, 1);
                set_train(tr);
                return 1;
            case 2:
                set_train(tr);
                return 1;
            }
        }
    }

    // возвращает 1, если нашлись вагоны, куда можно запихнуть всех сразу
    // 0, если придется разделять на несколько вагонов
    int output_where_to_put_passangers(train& tr, int num) {
        // выводим информацию о вагонах, куда можно посадить всех вместе
        std::cout << std::endl << "You can put passengers in one of these carriages:" << std::endl;
        carriage* car_ptr = tr.get_carriages() + 1;
        int empty_places = 0;
        bool flag = false;
        for (int i = 1; i < tr.get_length(); i++, car_ptr++) {
            empty_places = car_ptr->maximum_capacity - car_ptr->occupied_seats_number;
            if (empty_places >= num) {
                std::cout << "Carriage #" << i << " empty seats left: " << empty_places << std::endl;
                flag = true;
            }
        }
        if (flag) return 1;

        std::cout << "Sorry, but you can't put all passengers in one carriage, but you can divide them in several ones:" << std::endl;
        tr.output_not_full_cars();
        std::cout << std::endl;
        return 0;
    }


    int put_in_differrent_cars(train& tr, int num) {
        int temp_num_of_pass;
        while (num) {
            if (!input_num_of_pass(temp_num_of_pass, num)) return 0;
            int res = occupy_seats(tr, temp_num_of_pass);
            if (!res) return 0;
            if (res == 1) {
                std::cout << std::endl << "Successfully added" << std::endl;
                num -= temp_num_of_pass;
                tr.output_not_full_cars();
                std::cout << std::endl;
            }
            // если res == -1, ничего не делаем, цикл продолжается           
        }
        return 1;
    }


    void clr() {
        std::cout << "\x1B[2J\x1B[H";
    }
}