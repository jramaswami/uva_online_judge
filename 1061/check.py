"""
Script to check test output.
"""


def parse_case_number(line):
    space = line.index(' ')
    colon = line.index(':')
    case_number = int(line[space+1:colon])
    return case_number


def parse_set(line):
    left = line.index('{')
    right = line.index('}')
    tokens = line[left+1:right].split(', ')
    return set(tokens)


def main():
    "Main program."
    import sys
    line_no = 1
    ok = True
    print(f"Checking {sys.argv[1]} and {sys.argv[2]} ...")
    with open(sys.argv[1]) as efile:
        with open(sys.argv[2]) as ofile:
            eline = efile.readline().strip()
            oline = ofile.readline().strip()
            ecase = parse_case_number(eline)
            ocase = parse_case_number(oline)
            if ecase != ocase:
                print(f"case {ocase} does not match {ecase} on line {line_no}")
                ok = False
            impossible = eline.find('IMPOSSIBLE')
            if impossible >= 0:
                if impossible != ocase.find('IMPOSSIBLE'):
                    print(f"IMPOSSIBLE expected on line {line_no}")
                    ok = False

            set_present = eline.find("{")
            if set_present >= 0:
                eset = parse_set(eline)
                oset = parse_set(oline)
                if eset != oset:
                    print(f"{oset} does not match {eset} on line {line_no}")
                    ok = False
            else:
                if eline != oline:
                    print(f"{oline} does not match {eline} on line {line_no}")
                    ok = False

    if ok:
        print(f"{sys.argv[2]} ok")
    else:
        print(f"{sys.argv[2]} ERROR")


if __name__ == '__main__':
    main()
