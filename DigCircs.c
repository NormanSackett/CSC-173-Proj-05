#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Circuit.h"

static Circuit CircA() {
    char *title = "An and gate and an inverter put into an or gate";

    int num_inputs = 2;
    Boolean x = new_Boolean(0);
    Boolean y = new_Boolean(0);
    Boolean *inputs = new_Boolean_array(num_inputs);
    inputs[0] = x;
    inputs[1] = y;

    int num_outputs = 1;
    Boolean result = new_Boolean(0);
    Boolean *outputs = new_Boolean_array(num_outputs);
    outputs[0] = result;

    int num_gates = 3;
    Gate A1 = new_AndGate();
    Gate N1 = new_Inverter();
    Gate O1 = new_OrGate();
    Gate *gates = new_Gate_array(num_gates);
    gates[0] = A1;
    gates[1] = N1;
    gates[2] = O1;

    Circuit circuit = new_Circuit(title, num_inputs, inputs, num_outputs, outputs, num_gates, gates);

    Circuit_connect(circuit, x, Gate_getInput(A1, 0));
    Circuit_connect(circuit, y, Gate_getInput(A1, 1));
    Boolean x_and_y = Gate_getOutput(A1);

    Circuit_connect(circuit, x, Gate_getInput(N1, 0));
    Boolean not_x = Gate_getOutput(N1);

    Circuit_connect(circuit, x_and_y, Gate_getInput(O1, 0));
    Circuit_connect(circuit, not_x, Gate_getInput(O1, 1));
    Boolean x_and_y_or_not_x = Gate_getOutput(O1);

    Circuit_connect(circuit, x_and_y_or_not_x, result);
    return circuit;
}

static Circuit CircB() {
    char *title = "Three nor gates";

    int num_inputs = 2;
    Boolean x = new_Boolean(0);
    Boolean y = new_Boolean(0);
    Boolean *inputs = new_Boolean_array(num_inputs);
    inputs[0] = x;
    inputs[1] = y;

    int num_outputs = 1;
    Boolean result = new_Boolean(0);
    Boolean *outputs = new_Boolean_array(num_outputs);
    outputs[0] = result;

    int num_gates = 6;
    Gate A1 = new_OrGate();
    Gate N1 = new_Inverter();
    Gate A2 = new_OrGate();
    Gate N2 = new_Inverter();
    Gate A3 = new_OrGate();
    Gate N3 = new_Inverter();
    Gate *gates = new_Gate_array(num_gates);
    gates[0] = A1;
    gates[1] = N1;
    gates[2] = A2;
    gates[3] = N2;
    gates[4] = A3;
    gates[5] = N3;

    Circuit circuit = new_Circuit(title, num_inputs, inputs, num_outputs, outputs, num_gates, gates);

    Circuit_connect(circuit, x, Gate_getInput(A1, 0));
    Circuit_connect(circuit, y, Gate_getInput(A1, 1));
    Boolean x_or_y_1 = Gate_getOutput(A1);
    Circuit_connect(circuit, x_or_y_1, Gate_getInput(N1, 0));
    Boolean x_nor_y_1 = Gate_getOutput(N1);

    Circuit_connect(circuit, x, Gate_getInput(A2, 0));
    Circuit_connect(circuit, y, Gate_getInput(A2, 1));
    Boolean x_or_y_2 = Gate_getOutput(A2);
    Circuit_connect(circuit, x_or_y_2, Gate_getInput(N2, 0));
    Boolean x_nor_y_2 = Gate_getOutput(N2);

    Circuit_connect(circuit, x_nor_y_1, Gate_getInput(A3, 0));
    Circuit_connect(circuit, x_nor_y_2, Gate_getInput(A3, 1));
    Boolean or_nor = Gate_getOutput(A3);
    Circuit_connect(circuit, or_nor, Gate_getInput(N3, 0));
    Boolean nor_3 = Gate_getOutput(N3);

    Circuit_connect(circuit, nor_3, result);
    return circuit;
}

static Circuit CircC() {
    char *title = "Three inputs that have to be all true or all false";

    int num_inputs = 3;
    Boolean x = new_Boolean(0);
    Boolean y = new_Boolean(0);
    Boolean z = new_Boolean(0);
    Boolean *inputs = new_Boolean_array(num_inputs);
    inputs[0] = x;
    inputs[1] = y;
    inputs[2] = z;

    int num_outputs = 1;
    Boolean result = new_Boolean(0);
    Boolean *outputs = new_Boolean_array(num_outputs);
    outputs[0] = result;

    int num_gates = 8;
    Gate N1 = new_Inverter();
    Gate N2 = new_Inverter();
    Gate N3 = new_Inverter();
    Gate O1 = new_OrGate();
    Gate O2 = new_OrGate();
    Gate O3 = new_OrGate();
    Gate A1 = new_AndGate();
    Gate A2 = new_AndGate();
    Gate *gates = new_Gate_array(num_gates);
    gates[0] = N1;
    gates[1] = N2;
    gates[2] = N3;
    gates[3] = O1;
    gates[4] = O2;
    gates[5] = O3;
    gates[6] = A1;
    gates[7] = A2;

    Circuit circuit = new_Circuit(title, num_inputs, inputs, num_outputs, outputs, num_gates, gates);
    
    Circuit_connect(circuit, x, Gate_getInput(N1, 0));
    Boolean not_x = Gate_getOutput(N1);

    Circuit_connect(circuit, y, Gate_getInput(N2, 0));
    Boolean not_y = Gate_getOutput(N2);

    Circuit_connect(circuit, z, Gate_getInput(N3, 0));
    Boolean not_z = Gate_getOutput(N3);

    Circuit_connect(circuit, x, Gate_getInput(O1, 0));
    Circuit_connect(circuit, not_y, Gate_getInput(O1, 1));
    Boolean x_or_not_y = Gate_getOutput(O1);

    Circuit_connect(circuit, y, Gate_getInput(O2, 0));
    Circuit_connect(circuit, not_z, Gate_getInput(O2, 1));
    Boolean y_or_not_z = Gate_getOutput(O2);

    Circuit_connect(circuit, z, Gate_getInput(O3, 0));
    Circuit_connect(circuit, not_x, Gate_getInput(O3, 1));
    Boolean z_or_not_x = Gate_getOutput(O3);

    Circuit_connect(circuit, x_or_not_y, Gate_getInput(A1, 0));
    Circuit_connect(circuit, y_or_not_z, Gate_getInput(A1, 1));
    Boolean and_1 = Gate_getOutput(A1);

    Circuit_connect(circuit, and_1, Gate_getInput(A2, 0));
    Circuit_connect(circuit, z_or_not_x, Gate_getInput(A2, 1));
    Boolean and_2 = Gate_getOutput(A2);

    Circuit_connect(circuit, and_2, result);
    return circuit;
}

static Circuit ExtraCreditCirc() {
    char *title = "Extra credit truth table modelled with minterms";

    int num_inputs = 3;
    Boolean a = new_Boolean(0);
    Boolean b = new_Boolean(0);
    Boolean c = new_Boolean(0);
    Boolean *inputs = new_Boolean_array(num_inputs);
    inputs[0] = a;
    inputs[1] = b;
    inputs[2] = c;

    int num_outputs = 2;
    Boolean f = new_Boolean(0);
    Boolean g = new_Boolean(0);
    Boolean *outputs = new_Boolean_array(num_outputs);
    outputs[0] = f;
    outputs[1] = g;

    int num_gates = 20;
    Gate N1 = new_Inverter();
    Gate N2 = new_Inverter();
    Gate N3 = new_Inverter();

    Gate A1 = new_AndGate();
    Gate A2 = new_AndGate();
    Gate A3 = new_AndGate();
    Gate A4 = new_AndGate();
    Gate A5 = new_AndGate();
    Gate A6 = new_AndGate();
    Gate A7 = new_AndGate();
    Gate A8 = new_AndGate();
    Gate A9 = new_AndGate();
    Gate A10 = new_AndGate();
    Gate A11 = new_AndGate();

    Gate O1 = new_OrGate();
    Gate O2 = new_OrGate();
    Gate O3 = new_OrGate();
    Gate O4 = new_OrGate();
    Gate O5 = new_OrGate();
    Gate O6 = new_OrGate();
    Gate *gates = new_Gate_array(num_gates);
    gates[0] = N1;
    gates[1] = N2;
    gates[2] = N3;

    gates[3] = A1;
    gates[4] = A2;
    gates[5] = A3;
    gates[6] = A4;
    gates[7] = A5;
    gates[8] = A6;
    gates[9] = A7;
    gates[10] = A8;
    gates[11] = A9;
    gates[12] = A10;
    gates[13] = A11;

    gates[14] = O1;
    gates[15] = O2;
    gates[16] = O3;
    gates[17] = O4;
    gates[18] = O5;
    gates[19] = O6;

    Circuit circuit = new_Circuit(title, num_inputs, inputs, num_outputs, outputs, num_gates, gates);
    
    Circuit_connect(circuit, a, Gate_getInput(N1, 0));
    Boolean not_a = Gate_getOutput(N1);

    Circuit_connect(circuit, b, Gate_getInput(N2, 0));
    Boolean not_b = Gate_getOutput(N2);

    Circuit_connect(circuit, c, Gate_getInput(N3, 0));
    Boolean not_c = Gate_getOutput(N3);

    Circuit_connect(circuit, not_a, Gate_getInput(A1, 0));
    Circuit_connect(circuit, not_b, Gate_getInput(A1, 1));
    Boolean not_a_and_not_b = Gate_getOutput(A1);
    Circuit_connect(circuit, not_a_and_not_b, Gate_getInput(A2, 0));
    Circuit_connect(circuit, not_c, Gate_getInput(A2, 1));
    Boolean not_all = Gate_getOutput(A2);

    Circuit_connect(circuit, not_a_and_not_b, Gate_getInput(A3, 0));
    Circuit_connect(circuit, c, Gate_getInput(A3, 1));
    Boolean not_a_and_not_b_and_c = Gate_getOutput(A3);

    Circuit_connect(circuit, not_a, Gate_getInput(A4, 0));
    Circuit_connect(circuit, b, Gate_getInput(A4, 1));
    Boolean not_a_and_b = Gate_getOutput(A4);
    Circuit_connect(circuit, not_a_and_b, Gate_getInput(A5, 0));
    Circuit_connect(circuit, c, Gate_getInput(A5, 1));
    Boolean not_a_and_b_and_c = Gate_getOutput(A5);

    Circuit_connect(circuit, a, Gate_getInput(A6, 0));
    Circuit_connect(circuit, b, Gate_getInput(A6, 1));
    Boolean a_and_b = Gate_getOutput(A6);
    Circuit_connect(circuit, a_and_b, Gate_getInput(A7, 0));
    Circuit_connect(circuit, c, Gate_getInput(A7, 1));
    Boolean a_and_b_and_c = Gate_getOutput(A7);

    Circuit_connect(circuit, not_all, Gate_getInput(O1, 0));
    Circuit_connect(circuit, not_a_and_not_b_and_c, Gate_getInput(O1, 1));
    Boolean f_or_1 = Gate_getOutput(O1);
    Circuit_connect(circuit, f_or_1, Gate_getInput(O2, 0));
    Circuit_connect(circuit, not_a_and_b_and_c, Gate_getInput(O2, 1));
    Boolean f_or_2 = Gate_getOutput(O2);
    Circuit_connect(circuit, f_or_2, Gate_getInput(O3, 0));
    Circuit_connect(circuit, a_and_b_and_c, Gate_getInput(O3, 1));
    Boolean f_or_final = Gate_getOutput(O3);

    Circuit_connect(circuit, not_a_and_b, Gate_getInput(A8, 0));
    Circuit_connect(circuit, not_c, Gate_getInput(A8, 1));
    Boolean not_a_and_b_and_not_c = Gate_getOutput(A8);

    Circuit_connect(circuit, a, Gate_getInput(A9, 0));
    Circuit_connect(circuit, not_b, Gate_getInput(A9, 1));
    Boolean a_and_not_b = Gate_getOutput(A9);
    Circuit_connect(circuit, a_and_not_b, Gate_getInput(A10, 0));
    Circuit_connect(circuit, not_c, Gate_getInput(A10, 1));
    Boolean a_and_not_b_and_not_c = Gate_getOutput(A10);

    Circuit_connect(circuit, a_and_b, Gate_getInput(A11, 0));
    Circuit_connect(circuit, not_c, Gate_getInput(A11, 1));
    Boolean a_and_b_and_not_c = Gate_getOutput(A11);

    Circuit_connect(circuit, not_all, Gate_getInput(O4, 0));
    Circuit_connect(circuit, not_a_and_b_and_not_c, Gate_getInput(O4, 1));
    Boolean g_or_1 = Gate_getOutput(O4);
    Circuit_connect(circuit, g_or_1, Gate_getInput(O5, 0));
    Circuit_connect(circuit, a_and_not_b_and_not_c, Gate_getInput(O5, 1));
    Boolean g_or_2 = Gate_getOutput(O5);
    Circuit_connect(circuit, g_or_2, Gate_getInput(O6, 0));
    Circuit_connect(circuit, a_and_b_and_not_c, Gate_getInput(O6, 1));
    Boolean g_or_final = Gate_getOutput(O6);

    Circuit_connect(circuit, f_or_final, f);
    Circuit_connect(circuit, g_or_final, g);
    return circuit;
}

void test_circuit(Circuit c, char* inputs, char* outputs) {
    printf(Circuit_getTitle(c));
    printf("\n");
    for (int i = 0; i < Circuit_numInputs(c); i++) {
        printf("%c\t", inputs[i]);
    }
    for (int i = 0; i < Circuit_numOutputs(c); i++) {
        printf("\t%c", outputs[i]);
    }
    printf("\n\n");

    for (int i = 0; i < pow(2, Circuit_numInputs(c)); i++) {
        for (int j = 0; j < Circuit_numInputs(c); j++) {
            bool truth_val = (((int) (i / pow(2, Circuit_numInputs(c) - 1 - j)) % 2) == 1) ? 1 : 0;
            Circuit_setInput(c, j, truth_val);
            printf("%d\t", truth_val);
        }
        printf("|");
        Circuit_update(c);
        for (int j = 0; j < Circuit_numOutputs(c); j++) {
            printf("\t%s", Boolean_toString(Circuit_getOutput(c, j)));
        }
        printf("\n");
    }
}

int main() {
    printf("Circuit A\n");
    test_circuit(CircA(), "xy", "a");
    printf("\nCircuit B\n");
    test_circuit(CircB(), "xy", "b");
    printf("\nCircuit C\n");
    test_circuit(CircC(), "xyz", "c");
    printf("\nExtra Circuit\n");
    test_circuit(ExtraCreditCirc(), "abc", "fg");
}
