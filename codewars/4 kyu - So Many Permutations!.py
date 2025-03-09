from itertools import permutations as p

def permutations(s):
    st = set()
    for k in p(list(s)):
        st.add("".join(k))
    return list(st)