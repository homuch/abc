ESTIMATOR = '/mnt/g/Study/homework/112_2/ICCADcontest2024/2024CADContestProblemA/test_case/cost_estimators/cost_estimator_1'
MODULE_NAME = 'top_809960632_810038711_1598227639_893650103'
JSON_LIB = '/mnt/g/Study/homework/112_2/ICCADcontest2024/2024CADContestProblemA/test_case/lib/lib1.json'
LOOK_UP_TABLE = 'look_up_table.json'
import json
import subprocess
import re
def gen_temp_verilog_file(gate_name):
    with open('temp.v', 'w') as f:
        f.write(
f'''module {MODULE_NAME} (
    a, b, c
);
    input a, b;
    output c;
    {gate_name} u1(a, b, c);
endmodule''')



def generate_look_up_table():
    json_lib = json.load(open(JSON_LIB))
    look_up_table = {}
    for cell in json_lib['cells']:
        cell_name = cell['cell_name']
        if cell_name.find('not') != -1:
            continue
        if cell_name.find('buf') != -1:
            continue
        
        gen_temp_verilog_file(cell_name)
        # ./cost_estimators/cost_estimator_2 -library lib/lib1.json -netlist examples/toy_case1.v -output cf2_ex1.out
        result = subprocess.run([
            ESTIMATOR,
            '-library', JSON_LIB,
            '-netlist', 'temp.v',
            '-output', 'temp.out'
        ],capture_output=True, text=True, check=True)
        # print(result.stdout)
        # print("command: ", ' '.join(result.args))
        match = re.search(r"cost = ([\d.]+)", result.stdout)
        assert match is not None, f"Error: {result.stdout}"
        look_up_table[cell_name] = float(match.group(1))


    with open(LOOK_UP_TABLE, 'w') as f:
        json.dump(look_up_table, f, indent=4)

def main():
    generate_look_up_table()

if __name__ == '__main__':
    main()