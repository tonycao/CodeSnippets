def paren(num_open, num_close, balance_factor, paren_list):
    if num_open + num_close == 0:
        print "".join(paren_list)
        return

    if balance_factor > 0 and num_close > 0:
        paren_list.append(")")
        paren(num_open, num_close-1, balance_factor-1, paren_list)
        paren_list.pop()

    if num_open > 0:
        paren_list.append("(")
        paren(num_open -1, num_close, balance_factor+1, paren_list)
        paren_list.pop()

def paren_gen(n):
    print "n =", n
    paren(n, n, 0, [])
    print "-----"

def main():
    paren_gen(2)
    paren_gen(3)
    paren_gen(4)

if __name__ == "__main__":
    main()
