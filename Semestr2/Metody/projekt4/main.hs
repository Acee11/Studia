{-# OPTIONS_GHC -fno-warn-tabs #-}
module Main where
import System.Environment
import Slownie

main :: IO ()
main = do
	[number , currency] <- getArgs
	let num = read number :: Integer
	putStrLn $ slownie (toCurrency currency) num
	return ()