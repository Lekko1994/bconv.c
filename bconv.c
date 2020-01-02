#include <stdio.h>
#include <string.h>
#include <stdint.h>


int main(int argc,char *argv[]) {
    //I am checking if second argument is equal to "unsigned"
    if(strcmp(argv[1], "unsigned") == 0){
        char u[34];
        fgets(u, 34, stdin);
        char old_base[4];
        fgets(old_base, 4, stdin);
        char new_base[4];
        fgets(new_base, 4, stdin);
        // converting old_base and new_base from char to int
        int old_base_int = 0;
        for(int i = 0; i < (strlen(old_base) - 1); i++){
            old_base_int = old_base_int * 10 + (old_base[i] - 48);
        }
        int new_base_int = 0;
        for(int i = 0; i < (strlen(new_base) - 1); i++){
            new_base_int = new_base_int * 10 + (new_base[i] - 48);
        }
        
        // converting u from old base to base 10
        int u_index;
        int u_in_base_10 = 0;
        for(int i = 0; i < (strlen(u) - 1); i++){
            // converting u indices from char to int
            if(u[i] > 64){
                u_index = u[i] - 55;
            } else {
                u_index = u[i] - 48;
            }
            u_in_base_10 = u_in_base_10 * old_base_int + u_index;
        }

        // then change u from base 10 to new_base
        int total = u_in_base_10;
        int old_total;
        int remainder;
        char inserted_letter;
        char reverse_order_result[33] = "";
        char result[34] = "";
        int i = 0;
        if(total == 0){
            result[0] = '0';
        }
        // this while loop finds make the divisions and finds all the remainders
        // then it stores them into reverse_order_result
        // I was using two arrays: reverse_order_result
        // and result because reminders has to be shown
        //in the opposite order they were calculated
        while(total != 0){
            old_total = total;
            total = total / new_base_int;
            remainder = old_total - total * new_base_int;
            if(remainder < 10)
                inserted_letter = remainder + 48;
            if(remainder > 9)
                inserted_letter = remainder + 55;
            reverse_order_result[i] = inserted_letter;
            i++;
        }
        for(int i = 0; i < strlen(reverse_order_result); i++){
            result[i] = reverse_order_result[strlen(reverse_order_result) - i - 1];
        }
        printf("%s\n", result);
        
    } else if (strcmp(argv[1],"signed") == 0 ){
        char user_input[34];
        fgets(user_input, 34, stdin);
        
        // converting string user_input from string to decimal int
        int user_input_int = 0;
        if(strncmp(user_input,"-",1) == 0){
            for(int i = 1; i < (strlen(user_input) - 1); i++){
                user_input_int = user_input_int * 10 + (user_input[i] - 48);
            }
        } else {
            for(int i = 0; i < (strlen(user_input) - 1); i++){
                user_input_int = user_input_int * 10 + (user_input[i] - 48);
            }
        }
        
        int total = user_input_int;
        int old_total;
        int remainder;
        // initialization of the array needed for CSIF computers
        int reverse_order_result[32];
        for (int i = 0; i < 32; i++)
            reverse_order_result[i] = 0;
        int result[32];
        int i = 0;
        while(total != 0){
            old_total = total;
            total = total / 2;
            remainder = old_total - total * 2;
            reverse_order_result[i] = remainder;
            i++;
        }
        
        int length = sizeof(reverse_order_result)/sizeof(int);
        for(int i = length; i < 31; i++){
            reverse_order_result[i] = 0;
        }
        if(strncmp(user_input,"-",1)  == 0){
            reverse_order_result[31] = 1;
        } else {
            reverse_order_result[31] = 0;
        }
        

        
        //reversing the array by inserting its value in new array in the opposite order
        for(int i = 0; i < 32; i++){
            result[i] = reverse_order_result[31 - i];
        }
        // converting binary array to hexadecimal characters and printing them out
        int l = 0;
        int num = 0;
        char letter;
        while(l < 32){
            num = result[l] * 8 + result[l + 1] * 4 + result[l + 2] * 2 + result[l + 3] * 1;
            if(num <10)
                letter = num + 48;
            if(num > 9)
                letter = num + 55;
            printf("%c", letter);
            l = l + 4;
        }
        printf("\n");

        // 32-bit two’s complement hexadecimal representation
        if(strncmp(user_input, "-", 1)  == 0){
        for(int i = 1; i < 32; i++){
            if(result[i] == 0){
                result[i] = 1;
            } else {
                result[i] = 0;
            }
        }
        for(int i = 31; i >= 0; i--){
            if(result[i] == 0){
                result[i] = 1;
                break;
            } else {
                result[i] = 0;
            }
        }
        }
        // converting binary array to hexadecimal characters and printing them out
        l = 0;
        num = 0;
        while(l < 32){
            num = result[l] * 8 + result[l + 1] * 4 + result[l + 2] * 2 + result[l + 3] * 1;
            if(num <10)
                letter = num + 48;
            if(num > 9)
                letter = num + 55;
            printf("%c",letter);
            l = l + 4;
        }
        printf("\n");
        //checking if argument = "float"
    } else if (strcmp(argv[1], "float") == 0 ){
        float float_value = 0.0;
        scanf("%f", &float_value);
        //special case when input is 0
        if(float_value == 0){
            printf("0 E0\n");
        }
        // getting the binary of input
        uint32_t float_bits = *((uint32_t*)&float_value);
        // in case input is not 0, the rest of the code is executed
        if(float_value != 0){
        // moving 31 bits to the right within float_bits and check if it becomess 0 = false or 1 = true
        // this way we know if its positive or negative number
        if(float_bits >> 31){
            printf("-1.");
        } else {
            printf("1.");
        }
        // printing out last 23 binary digits of float input
        unsigned i;
        for (i = 1 << 22; i > 0; i = i / 2)
            (float_bits & i)? printf("1"):printf("0");
        printf(" E");
        // creating a new 32 bits int, copy the value
        // of float_bits and moving by 23 bits to the right
        uint32_t float_bits_moved = float_bits >> 23;
        // storing most right 8 bits into char
        unsigned char exp = float_bits_moved;
        // exp - bias
        int E = exp - 127;
        //change E to binary and print it out
        int total = E;
        int old_total;
        int remainder;
        int reverse_order_result2[8];
        int count = 0;
        while(total != 0){
            old_total = total;
            total = total / 2;
            remainder = old_total - total * 2;
        // remainder is negative when there is
        // - after e in the input. Multiplication by -1
        //gives positive number. However the last remainder
        //must stay negative to show correct output
            if(remainder < 0 && total != 0){
                remainder = remainder * (-1);
            }
            reverse_order_result2[count] = remainder;
            count++;
        }
        for(int i = count - 1; i >= 0; i--){
            printf("%d",reverse_order_result2[i]);
        }
        printf("\n");
        }
    }
    return 0;
}
