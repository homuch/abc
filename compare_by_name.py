import argparse
import json
LOOK_UP_TABLE = '/home/homu/ICCAD-contest2024/look_up_table.json'

def compare_by_name(name1, name2):
    if name1 == name2:
        return 0
    with open(LOOK_UP_TABLE) as f:
        look_up_table = json.load(f)
    # less cost is better
    return int(look_up_table[name1] > look_up_table[name2])

def main():
    parser = argparse.ArgumentParser(description='Compare two names')
    parser.add_argument('name1', help='First name to compare')
    parser.add_argument('name2', help='Second name to compare')
    args = parser.parse_args()
    result = compare_by_name(args.name1, args.name2)
    print(result)
    # if result == 0:
    #     print('The names are the same')
    # elif result:
    #     print(f'{args.name1} is shorter than {args.name2}')
    # else:
    #     print(f'{args.name1} is longer than {args.name2}')


if __name__ == '__main__':
    main()