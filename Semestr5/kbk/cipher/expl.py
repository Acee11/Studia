from ciphertext import ct
from collections import Counter

def enc(m, perm):
    return ''.join([perm[c] for c in m])

pt_freq = 'E T A O I N S H R D L C U M W F G Y P B V K J X Q Z'
ct_freq = 'D V Y F Q Z C B J A O P S W M N T L I K R X E H G U'

pt_freq = pt_freq.replace(' ', '')
ct_freq = ct_freq.replace(' ', '')

# PEACOU ARTCSEARTATIVE
# JDWDWKDJA

g =  Counter(ct).most_common(26)
perm = dict(zip(ct_freq, pt_freq))

print g
print
print enc(ct, perm)
print
print ct


# for i in range(4,len(ct_freq)-1):
#     for j in range(4,len(ct_freq)-1):
#         if j == i:
#             continue
#         ctf = list(ct_freq)
#         ctf[i], ctf[i+1] = ctf[i+1], ctf[i]
#         ctf[j], ctf[j+1] = ctf[j+1], ctf[j]
#         ctf = ''.join(ctf)
#         perm = dict(zip(ctf, pt_freq))
#         print '-'*100
#         print ctf
#         print '-'*100
#         print enc(ct, perm)
#         print '-'*100


