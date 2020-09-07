# ask a text to the user
text = input("Text: ")

# number of letters, words and sentences in the text
# number of letters = summ of any charcter between a and z or A and Z
nLetters = 0
# number of words = sum of sequences of characters separeted by space
nWords = 1
# number of sentences = sum of "!, ? or ."
nSentences = 0


i = 0

for i in range(len(text)):
    if (ord(text[i]) >= 65 and ord(text[i]) <= 90) or (ord(text[i]) >= 97 and ord(text[i]) <= 122):
        # letter
        nLetters += 1
    elif ord(text[i]) == 32:
        # words
        nWords += 1
    elif ord(text[i]) == 33 or ord(text[i]) == 46 or ord(text[i]) == 63:
        # sentences
        nSentences += 1


# print(f'nLetters: {nLetters}')
# print(f'nWords: {nWords}')
# print(f'nSentences: {nSentences}')

L = float(nLetters) / float(nWords) * 100
S = float(nSentences) / float(nWords) * 100
index = 0.0588 * L - 0.296 * S - 15.8
# print(f'index: {index}')
index = round(index)
# print(f'index: {index}')
# print(f'L: {L}')
# print(f'S: {S}')

print
# print grade (int)
#   if grade >= 16 print Grade 16+
#   if grade <1 print Grade 1

# printf("nLetters= %i\n", nLetters);
# printf("nWords= %i\n", nWords);
# printf("nSentences= %i\n", nSentences);


if index >= 16:
    print("Grade 16+")
elif (index < 1):
    print("Before Grade 1")
else:
    print(f"Grade {int(index)}")
