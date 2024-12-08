#include <iostream>
#include <fstream>   // Thư viện để lưu điểm số vào file
#include <cstdlib>   // Thư viện cho hàm rand()
#include <ctime>     // Thư viện để lấy thời gian làm seed
#include <string>    // Thư viện xử lý chuỗi

// Hàm hiển thị trạng thái hiện tại
void displayStatus(int playerHP, int monsterHP) {
    std::cout << "=========================\n";
    std::cout << "Người chơi: " << playerHP << " HP\n";
    std::cout << "Quái vật: " << monsterHP << " HP\n";
    std::cout << "=========================\n";
}

// Hàm chơi game
int playGame() {
    int playerHP = 100;   // Máu của người chơi
    int monsterHP = 80;   // Máu của quái vật
    int playerAttack, monsterAttack;

    // Khởi tạo số ngẫu nhiên
    std::srand(std::time(0));

    std::cout << "Trò chơi bắt đầu! Bạn đang chiến đấu với quái vật.\n";

    while (playerHP > 0 && monsterHP > 0) {
        // Hiển thị trạng thái
        displayStatus(playerHP, monsterHP);

        // Người chơi tấn công
        std::cout << "Tấn công quái vật (ấn Enter)...\n";
        std::cin.get();
        playerAttack = std::rand() % 20 + 5;  // Sát thương: 5 - 25
        monsterHP -= playerAttack;
        std::cout << "Bạn gây " << playerAttack << " sát thương lên quái vật!\n";

        if (monsterHP <= 0) {
            std::cout << "Bạn đã đánh bại quái vật! Chúc mừng!\n";
            return playerHP;  // Trả về máu còn lại của người chơi
        }

        // Quái vật tấn công
        monsterAttack = std::rand() % 15 + 5;  // Sát thương: 5 - 20
        playerHP -= monsterAttack;
        std::cout << "Quái vật gây " << monsterAttack << " sát thương lên bạn!\n";

        if (playerHP <= 0) {
            std::cout << "Bạn đã bị quái vật đánh bại. Game over!\n";
            return 0;  // Trả về 0 khi thua
        }
    }
    return 0;  // Dự phòng
}

// Hàm lưu điểm số vào file
void saveScore(int score) {
    std::ofstream file("scores.txt", std::ios::app);  // Mở file ở chế độ thêm
    if (file.is_open()) {
        std::string playerName;
        std::cout << "Nhập tên của bạn: ";
        std::cin.ignore();  // Xóa bộ nhớ đệm
        std::getline(std::cin, playerName);
        file << playerName << " - " << score << " HP còn lại\n";
        file.close();
        std::cout << "Điểm số đã được lưu!\n";
    } else {
        std::cerr << "Không thể mở file để lưu điểm số.\n";
    }
}

// Hàm hiển thị menu
void displayMenu() {
    std::cout << "=============================\n";
    std::cout << "Chào mừng bạn đến với trò chơi đánh quái vật!\n";
    std::cout << "1. Chơi game\n";
    std::cout << "2. Lưu điểm số\n";
    std::cout << "3. Thoát\n";
    std::cout << "=============================\n";
    std::cout << "Chọn một tùy chọn: ";
}

// Hàm chính
int main() {
    int choice;
    int lastScore = 0;  // Lưu điểm số của lần chơi gần nhất

    do {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::cin.ignore();  // Xóa bộ nhớ đệm trước khi dùng `std::cin.get()`
                lastScore = playGame();
                break;
            }
            case 2: {
                if (lastScore > 0) {
                    saveScore(lastScore);
                } else {
                    std::cout << "Bạn chưa có điểm để lưu. Hãy chơi game trước!\n";
                }
                break;
            }
            case 3:
                std::cout << "Cảm ơn bạn đã chơi! Tạm biệt!\n";
                break;
            default:
                std::cout << "Lựa chọn không hợp lệ. Vui lòng chọn lại.\n";
                break;
        }
    } while (choice != 3);

    return 0;
}
