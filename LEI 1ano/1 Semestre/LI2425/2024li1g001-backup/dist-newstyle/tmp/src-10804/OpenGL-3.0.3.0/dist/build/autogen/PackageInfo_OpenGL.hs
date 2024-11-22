{-# LANGUAGE NoRebindableSyntax #-}
{-# OPTIONS_GHC -fno-warn-missing-import-lists #-}
{-# OPTIONS_GHC -w #-}
module PackageInfo_OpenGL (
    name,
    version,
    synopsis,
    copyright,
    homepage,
  ) where

import Data.Version (Version(..))
import Prelude

name :: String
name = "OpenGL"
version :: Version
version = Version [3,0,3,0] []

synopsis :: String
synopsis = "A binding for the OpenGL graphics system"
copyright :: String
copyright = "Copyright (C) 2002-2019 Sven Panne"
homepage :: String
homepage = "https://wiki.haskell.org/OpenGL"
