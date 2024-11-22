{-# LANGUAGE CPP #-}
{-# LANGUAGE NoRebindableSyntax #-}
#if __GLASGOW_HASKELL__ >= 810
{-# OPTIONS_GHC -Wno-prepositive-qualified-module #-}
#endif
{-# OPTIONS_GHC -fno-warn-missing-import-lists #-}
{-# OPTIONS_GHC -w #-}
module Paths_OpenGL (
    version,
    getBinDir, getLibDir, getDynLibDir, getDataDir, getLibexecDir,
    getDataFileName, getSysconfDir
  ) where


import qualified Control.Exception as Exception
import qualified Data.List as List
import Data.Version (Version(..))
import System.Environment (getEnv)
import Prelude


#if defined(VERSION_base)

#if MIN_VERSION_base(4,0,0)
catchIO :: IO a -> (Exception.IOException -> IO a) -> IO a
#else
catchIO :: IO a -> (Exception.Exception -> IO a) -> IO a
#endif

#else
catchIO :: IO a -> (Exception.IOException -> IO a) -> IO a
#endif
catchIO = Exception.catch

version :: Version
version = Version [3,0,3,0] []

getDataFileName :: FilePath -> IO FilePath
getDataFileName name = do
  dir <- getDataDir
  return (dir `joinFileName` name)

getBinDir, getLibDir, getDynLibDir, getDataDir, getLibexecDir, getSysconfDir :: IO FilePath




bindir, libdir, dynlibdir, datadir, libexecdir, sysconfdir :: FilePath
bindir     = "/home/hugo/.cabal/store/ghc-9.4.8/OpenGL-3.0.3.0-88aa1061e0654516dd953ce7d8e57924d7033a18a2d6f3517c28d8458758bf3d/bin"
libdir     = "/home/hugo/.cabal/store/ghc-9.4.8/OpenGL-3.0.3.0-88aa1061e0654516dd953ce7d8e57924d7033a18a2d6f3517c28d8458758bf3d/lib"
dynlibdir  = "/home/hugo/.cabal/store/ghc-9.4.8/OpenGL-3.0.3.0-88aa1061e0654516dd953ce7d8e57924d7033a18a2d6f3517c28d8458758bf3d/lib"
datadir    = "/home/hugo/.cabal/store/ghc-9.4.8/OpenGL-3.0.3.0-88aa1061e0654516dd953ce7d8e57924d7033a18a2d6f3517c28d8458758bf3d/share"
libexecdir = "/home/hugo/.cabal/store/ghc-9.4.8/OpenGL-3.0.3.0-88aa1061e0654516dd953ce7d8e57924d7033a18a2d6f3517c28d8458758bf3d/libexec"
sysconfdir = "/home/hugo/.cabal/store/ghc-9.4.8/OpenGL-3.0.3.0-88aa1061e0654516dd953ce7d8e57924d7033a18a2d6f3517c28d8458758bf3d/etc"

getBinDir     = catchIO (getEnv "OpenGL_bindir")     (\_ -> return bindir)
getLibDir     = catchIO (getEnv "OpenGL_libdir")     (\_ -> return libdir)
getDynLibDir  = catchIO (getEnv "OpenGL_dynlibdir")  (\_ -> return dynlibdir)
getDataDir    = catchIO (getEnv "OpenGL_datadir")    (\_ -> return datadir)
getLibexecDir = catchIO (getEnv "OpenGL_libexecdir") (\_ -> return libexecdir)
getSysconfDir = catchIO (getEnv "OpenGL_sysconfdir") (\_ -> return sysconfdir)



joinFileName :: String -> String -> FilePath
joinFileName ""  fname = fname
joinFileName "." fname = fname
joinFileName dir ""    = dir
joinFileName dir fname
  | isPathSeparator (List.last dir) = dir ++ fname
  | otherwise                       = dir ++ pathSeparator : fname

pathSeparator :: Char
pathSeparator = '/'

isPathSeparator :: Char -> Bool
isPathSeparator c = c == '/'
