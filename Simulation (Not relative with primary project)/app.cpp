#include <iostream>
#include <bitset>
using namespace std;

uint8_t alu(uint8_t A, uint8_t B, bool S3, bool S2, bool S1, bool S0, bool Cin) {
    uint8_t result = 0;



    if (S3 == 0 && S2 == 0) {
        // Arithmetic Unit
        uint8_t arith_op = (S1 << 1) | S0;
        switch (arith_op) {
            case 0b00:
                result = Cin ? A + B + 1 : A + B; // ADD or ADD with Carry
                break;
            case 0b01:
                result = Cin ? A + (~B) + 1 : A + (~B); // SUB or SUB with Borrow
                break;
            case 0b10:
                result = A - 1; // Decrement
                break;
            case 0b11:
                result = A + 1; // Increment
                break;
        }
    } else if (S3 == 0 && S2 == 1) {
        // Logic Unit
        uint8_t logic_op = (S1 << 1) | S0;
        switch (logic_op) {
            case 0b00:
                result = A & B; // AND
                break;
            case 0b01:
                result = A | B; // OR
                break;
            case 0b10:
                result = A ^ B; // XOR
                break;
            case 0b11:
                result = ~A; // NOT A
                break;
        }
    } else if (S3 == 1 && S2 == 0) {
        // Shift Unit
        if (S1 == 0 && S0 == 0)
            result = A >> 1; // Logical Shift Right
        else if (S1 == 0 && S0 == 1)
            result = A << 1; // Logical Shift Left
        else
            cout << "Invalid Shift Operation\n";
    } else {
        cout << "Invalid ALU Control Signals (S3, S2)\n";
    }

    return result;
}



// The main function to testing
int main() {
    uint8_t A, B;
    bool S3, S2, S1, S0, Cin;

    cout << "Enter value for A (0-255): ";
    cin >> A;

    cout << "Enter value for B (0-255): ";
    cin >> B;

    cout << "Enter control bits S3 S2 S1 S0 (space separated, 0 or 1): ";
    cin >> S3 >> S2 >> S1 >> S0;

    cout << "Enter Cin (0 or 1): ";
    cin >> Cin;

    uint8_t result = alu(A, B, S3, S2, S1, S0, Cin);

    cout << "\nResult: " << (int)result << " (binary: " << bitset<8>(result) << ")\n";


    // program end
    return 0;
}
