from string import ascii_lowercase

def top_3_words(text):
    frq = dict()
    txt = "".join(map(lambda c: c if c in ascii_lowercase or c == "'" else ' ', text.lower())).split(' ')
    for word in txt: frq[word] = frq.get(word, 0) + 1
    top = sorted([(frq[x], x) for x in frq if x.replace("'", '') != ''], reverse = True)
    first = [t[1] for t in top]
    if len(first) < 3: return first
    return first[:3]