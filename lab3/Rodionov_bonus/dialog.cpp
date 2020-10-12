#include "dialog.h"

namespace Prog3C {
    static constexpr int options_number = 11;
    
    using opt_t = void(*)(train&);

    static const opt_t options[options_number] = {
        &set_train,
        &get_train_occupancy_information,
        &occupy_seats,
        &get_carriage_occupancy_information,
        &add_carriage,
        &unhook_train,
        &get_passengers_number,
		&get_average,
		&rearrange_train,
		&change_places,
		&add_new_passangers
    };

    void dialog(train &main_train) {
        int choice = 0;
        
        std::cout << "------------------------------------------------------------" << std::endl;
        while (true) {
           menu();
           std::cout << "------------------------------------------------------------" << std::endl;
           choice = getNum<int>("Your choice: ");
           std::cout << "------------------------------------------------------------" << std::endl;
           if (!choice) {
              break;
           }
           else if (choice < 0 || choice > options_number) {
              std::cout << "Invalid option detected!" << std::endl; 
           }
           else {
              options[choice - 1](main_train);
           }
           std::cout << "------------------------------------------------------------" << std::endl;
        }
    }
    
    void menu() {
        std::cout <<
            "0. Quit" << std::endl <<
            "1. Set train" << std::endl <<
            "2. Get train occupancy information" << std::endl <<
            "3. Occupy seat" << std::endl <<
            "4. Get carriage occupancy information" << std::endl <<
            "5. Add carriage to train" << std::endl <<
            "6. Train unhook" << std::endl <<
            "7. Get passengers number" << std::endl <<

			"8. Find average number of passengers in a carriage" << std::endl <<
			"9. Rearrange train" << std::endl << 
			"10. Transfer passengers to another carriage" << std::endl <<
			"11. Add new passengers to the train" << std::endl;
    }
    
    void set_train(train& main_train) {
        std::cout << "Train parameters: ";
        try {
            std::cin >> main_train;
        }
        catch (const std::invalid_argument& error) {
            std::cerr << "Error: " << error.what() << std::endl;
        }
    }
    
    void get_train_occupancy_information(train& main_train) {
        std::cout << main_train;
    }
    
    void occupy_seats(train& main_train) {
        int carriage_index = getNum<int>("Carriage index: ");      
        int seats_number = getNum<int>("Number of seats to be occupied: ");
        
        try {
            main_train(carriage_index, seats_number);
        }
        catch (const std::invalid_argument& error) {
            std::cerr << "Error: " << error.what() << std::endl;
        }
    }
    
    void get_carriage_occupancy_information(train& main_train) {
        int carriage_index = getNum<int>("Carriage index: ");
        
        try {
            int result = main_train[carriage_index];
            std::cout << "Number of passengers in the carriage: " << result << std::endl;
        }
        catch (const std::invalid_argument& error) {
            std::cerr << "Error: " << error.what() << std::endl;
        }        
    }
    
    void add_carriage(train& main_train) {
        int carriage_maximum_capacity = getNum<int>("Carriage maximum capacity: ");
        int carriage_occupied_seats_number = getNum<int>("Carriage occupied seats number: ");
        
        try {
            carriage main_carriage(carriage_maximum_capacity, carriage_occupied_seats_number);
            main_train += main_carriage;
        }
        catch (const std::invalid_argument& error) {
            std::cerr << "Error: " << error.what() << std::endl;
        }
    }
    
    void unhook_train(train& main_train) {
        int carriages_number = getNum<int>("Number of carriages to unhook: ");
        int *min_train = new int[carriages_number];
        struct carriage *mini_cars = new struct carriage[carriages_number];
              
        std::cout << "Carriages indexes: ";
        for (int i = 0; i < carriages_number; i++) {
            min_train[i] = getNum<int>("");
            mini_cars[i] = { main_train.get_carriages()[min_train[i]].maximum_capacity, main_train.get_carriages()[min_train[i]].occupied_seats_number };
        }
        
        try {
            main_train( carriages_number, min_train );
            train mini_train(mini_cars, carriages_number+1);
            train mini_train_copy(mini_train);
            std::cout << "------------------------------------------------------------" << std::endl;
            std::cout << "Formed mini-train occupancy information: " << std::endl;
            std::cout << "------------------------------------------------------------" << std::endl;
            std::cout << mini_train_copy;
        }
        catch (const std::invalid_argument& error) {
            std::cerr << "Error: " << error.what() << std::endl;
        }
    }
    
    void get_passengers_number(train& main_train) {
        std::cout << "Number of passengers in the train: " << main_train.get_passengers_number() << std::endl;
    }




	// 			########             ДОПОЛНИТЕЛЬНЫЕ ФУНКЦИИ   (Щербакова)        ######## 
		



	// среднее арифметическое, как ты предлагал
	void get_average(train& main_train) {
		double average = (double)main_train.get_passengers_number() / (main_train.get_length() - 1);
		std::cout << "Average number of passenges in a carriage: " << average << std::endl;
	}
	

	// функия сортирует вагоны в порядке убывания максимального кол-ва пассажиров в них
	// наверно, это не имеет особого практического смысла, но идея была в том, чтобы самые большие вагоны были ближе к локомотиву, а самые маленьке - в хвосте поезда
	void rearrange_train(train& main_train) {
		int length = main_train.get_length();
		// создается копия массива вагонов для последующей сортировки
		struct carriage* new_cars = new struct carriage[length - 1];
		for (int i = 1; i < length; i++) 
			new_cars[i - 1] = main_train.get_carriages()[i];

		// функция-компаратор чуть ниже написана (кстати, чтобы работал sort я еще <algorithm> подключила в dialog.h) 
		std::sort(new_cars, new_cars + length - 1, comp);
		main_train.set_carriages(new_cars, length);
		delete[] new_cars;

		// вывод информации о вагонах с указанием максимального кол-ва мест
		struct carriage temp_car;
		for (int i = 0; i < main_train.get_length(); i++) {
			temp_car = main_train.get_carriages()[i];
            std::cout << "Carriage #" << i << " occupancy: " << temp_car.occupied_seats_number << "/" << temp_car.maximum_capacity << " passenger(s)" << std::endl;
        }
	}


	bool comp(struct carriage left, struct carriage right) {
		return left.maximum_capacity > right.maximum_capacity;
	}


	// пересадить пассажиров из одного вагона в другой
	void change_places(train& main_train) {
		int length = main_train.get_length();

		// спрашиваем, из какого вагона надо переместить пассажиров
		int from_num = getNum<int>("Input number of carriage you want to move passengers from: ");
		if (from_num < 0 || from_num > length) {
			std::cerr << "Carriage does not exist" << std::endl;
			return;
		}
		struct carriage* from_car = main_train.get_carriages() + from_num;
		
		// спрашиваем, сколько пассажиров переместить
		int number_to_move = getNum<int>("Input number of passengers to move:");
		if (number_to_move <= 0 || number_to_move > from_car->occupied_seats_number) {
			std::cerr << "Incorrect input" << std::endl;
			return;
		}

		// выводим, в каких вагонах осталось достаточно свободных мест
		std::cout << std::endl << "You can move passengers to one of these carriages:" << std::endl;
		struct carriage* car_ptr = main_train.get_carriages() + 1;
		int empty_places = 0;
		bool flag = false;
		for (int i = 1; i < length; i++, car_ptr++) {
			empty_places = car_ptr->maximum_capacity - car_ptr->occupied_seats_number;
			if (i != from_num && empty_places >= number_to_move) {
				std::cout << "Carriage #" << i << " empty places left: " << empty_places << std::endl;
				flag = true;
			}
		}
		if (!flag) std::cerr << "Sorry, no places left in this train :(" << std::endl;
		
		// спрашиваем, в какой вагон переместить
		int to_num = 0;
		while (1) {
			to_num = getNum<int>("Input number of carriage you want to move passengers: ");
			if (to_num <= 0 || to_num > length) {
				std::cerr << "Carriage does not exist" << std::endl;	
				continue;
			}
			car_ptr = main_train.get_carriages() + to_num;
			int empty_seats = car_ptr->maximum_capacity - car_ptr->occupied_seats_number;

			if (empty_seats >= number_to_move) {
				car_ptr->occupied_seats_number += number_to_move;
				main_train.get_carriages()[from_num].occupied_seats_number -= number_to_move;
				std::cout << "Passengers moved successfully" << std::endl;
				return;
			}
			else std::cout << "Not enough empty seats in this carriage" << std::endl;
		}
	}

	
	// добавить пассажиров в один из существующих вагонов (именно всех в один вагон)
	void add_new_passangers(train& main_train) {

		int number_to_move = getNum<int>("Input number of passengers to add: ");
		if (number_to_move < 1) {std::cerr << "Invalid input" << std::endl; return;}
	
		// выводим, в каких вагонах осталось достаточно свободных мест
		std::cout << std::endl << "You can add passengers to one of these carriages:" << std::endl;
		struct carriage* car_ptr = main_train.get_carriages() + 1;
		int empty_places = 0;
		bool flag = false;
		for (int i = 1; i < main_train.get_length(); i++, car_ptr++) {
			empty_places = car_ptr->maximum_capacity - car_ptr->occupied_seats_number;
			if (empty_places >= number_to_move) {
				std::cout << "Carriage #" << i << " empty places left: " << empty_places << std::endl;
				flag = true;
			}
		}
		if (!flag) {
			std::cerr << "Sorry, no places left in this train :(" << std::endl;
			return;
		}

		// спрашиваем, в какой вагон посадить 
		int to_num = 0;
		flag = false;
		do {
			to_num = getNum<int>("Input number of carriage you want to move passengers: ");
			try { main_train(to_num, number_to_move); flag = true; }     // используется перегруженный оператор ()
			catch (const std::invalid_argument& error) { std::cerr << "Error: " << error.what() << std::endl; }
		} while (!flag);
	}

}