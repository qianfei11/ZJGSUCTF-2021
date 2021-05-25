#!/usr/bin/env sage

def GaussLatticeReduction(v1, v2):
    while True:
        if v2.norm() < v1.norm():
            v1, v2 = v2, v1
        m = round( v1*v2 / v1.norm()^2 )
        if m == 0:
            return (v1, v2)
        v2 = v2 - m*v1

h = 12135457627621292984228734685821598777710600237350345012431222247048148598100618736048854756943005450242847115238320402308616727416218423673756689396619547531089631520260320978457295359687766563515121895495107957023188905972284966786247818054486096208226981644283117842342045038791300501479203270310587811168495273573064682012016734746949472232889585386544214165430174005941123576030843306737889993677335852296022331773489012874404050682670792839572149558991448673252719588786787338069308592078405702385404310503399177849764199814990808352828759179897262257971331185248016692490628892006897852531387029466865272671314
g = 23929580434797245341216030807936166275806349588052117230581437217507485494711236359402642755601911546434680349972599897434783901135998655907182895862527415154095735154724958058486321777374265585383160004813969552865916893734852778478378011068275760001359148221226211072402689462010968876021963169679287765256855831546084070710107495451794440866923080167628631226224810247473947177473909149464503812142639331415526898349915619639192622250590679519462772538036678961719881336932678542504254314502644092469818888546449813122818027353614358120607717465879159337263236939327398972649720384013785956520131527776018467886263

# Construct lattice
v1 = vector(ZZ, [1, h])
v2 = vector(ZZ, [0, g])
m = matrix([v1, v2])

# Solve SVP
shortest_vector = m.LLL()[0]
#shortest_vector = GaussLatticeReduction(v1, v2)[0]
p, r = shortest_vector
p, r = abs(p), abs(r)
print(p, r)

# Decrypt
c_ = 15021030893255945170942112085130416851868982802343557703595300271482057634860020804503462537922826305521268278213688129971502205729006132337611416902812249227627612909023187812085657117623636732409565423968161954597228563651112288811775017233542925709274039336450802087867088152992605995971345818873603181664579539668144861814966479977665936037983685643560332279637642802644854112936339752331116265054262543101047399225842984665814466206730569310919680826331252144586365772506361948665079332285620583595986530293705134202337060217399707451036811277859141801423766960746233767173558691620894062825077049943662767513962
n = 25083699027391429203697653004128815822517282475709554848295600879734396331413962053576582172929274388962043374501660913966535376704444442087479450180514454567206603356450437023001670573907067544265678326807735677245267943374154421788861789249895920292481742889457475242131112246184386628004330850426242255820450776071206836282620262923264066876849362524034422625552930072481868760721556192987364453945577221206147446545793711334961134995685825803612008094068374693120105064446182451631088566287951917516810481355317851505142796793148404169099278459144708849631862150670904508037457807026933526667449405849023854949681
e = 65537
q = n / p
print 'q = ' + str(q)
phi = (p - 1) * (q - 1)
d = inverse_mod(e, phi)
r_ = inverse_mod(r, n)
c = (c_ * r_) % n
m = pow(c, d, n)
print m
print hex(int(m))[2:].strip('L').decode('hex')
