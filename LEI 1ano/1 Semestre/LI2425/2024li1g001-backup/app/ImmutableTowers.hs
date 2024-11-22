module ImmutableTowers where


import LI12425

data ImmutableTowers = ImmutableTowers {}


mapaexemplo :: Mapa
mapaexemplo =[  [t, t, r, a, a, a],
                [r, t, r, a, r, r],
                [r, t, r, a, r, t],
                [r, t, r, a, r, t],
                [r, t, t, t, t, t],
                [a, a, a, a, r, r]]
    where
        t = Terra
        r = Relva
        a = Agua

mapa01 :: Mapa
mapa01 = [[r, r, r, r, a, a, a, r],
          [r, t, t, r, a, r, r, r],
          [r, t, r, r, a, r, t, r],
          [r, t, r, r, a, r, t, r],
          [r, t, r, r, a, r, t, r],
          [r, t, t, t, t, t, t, r],
          [r, r, r, r, a, a, r, r],
          [r, r, r, r, r, a, r, r]]
    where
        t = Terra
        r = Relva
        a = Agua

mapa02 :: Mapa
mapa02 = [[r, r, r, r, a, a, r, r],
          [r, t, t, t, a, r, r, r],
          [r, t, r, r, a, r, r, r],
          [r, t, r, r, a, r, r, r],
          [r, t, r, t, t, t, t, r],
          [r, t, t, t, a, r, r, r],
          [a, a, a, a, a, r, r, r],
          [r, r, r, r, r, r, r, r]]
    where
        t = Terra
        r = Relva
        a = Agua

mapa03 :: Mapa
mapa03 = [[r, r, r, a, a, r, r, r],
          [r, t, t, t, a, r, r, r],
          [r, r, r, t, a, r, r, r],
          [r, r, r, t, t, t, t, r],
          [r, a, r, r, r, t, r, r],
          [r, a, r, r, r, t, r, r],
          [a, a, r, r, r, t, r, r],
          [r, r, r, r, r, r, r, r]]
    where
        t = Terra
        r = Relva
        a = Agua
