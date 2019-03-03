module Hw2 where

import Data.List -- YOU MAY USE THIS MODULE FOR SORTING THE AGENTS

data Level = Newbie | Intermediate | Expert deriving (Enum, Eq, Ord, Show, Read)
data Hunter = Hunter {hID::Int, hlevel::Level, hEnergy::Int, hNumberOfCatches::Int, hActions::[Direction]} deriving (Eq, Show, Read)
data Prey = Prey {pID::Int, pEnergy::Int, pActions::[Direction]} deriving (Eq, Show, Read)
data Cell = O | X | H Hunter | P Prey | T deriving (Eq, Show, Read)
data Direction = N | S | E | W deriving (Eq, Show, Read)
type Coordinate = (Int, Int)
-- DO NOT CHANGE THE DEFINITIONS ABOVE. --


-- INSTANCES OF Ord FOR SORTING, UNCOMMENT AND COMPLETE THE IMPLEMENTATIONS --


instance Ord Hunter where 
    compare h1 h2
        | hlevel h1 > hlevel h2 = GT
        | hlevel h2 > hlevel h1 = LT
        | (hlevel h1 == hlevel h2) && (hEnergy h1 > hEnergy h2) = GT
        | (hlevel h1 == hlevel h2) && (hEnergy h1 < hEnergy h2) = LT
        | (hlevel h1 == hlevel h2) && (hEnergy h2 == hEnergy h1) && (hNumberOfCatches h1 > hNumberOfCatches h2) = GT
        | (hlevel h1 == hlevel h2) && (hEnergy h2 == hEnergy h1) && (hNumberOfCatches h1 < hNumberOfCatches h2) = LT
        | (hlevel h1 == hlevel h2) && (hEnergy h2 == hEnergy h1) && (hNumberOfCatches h1 == hNumberOfCatches h2) && (hID h1 < hID h2) = GT
        | (hlevel h1 == hlevel h2) && (hEnergy h2 == hEnergy h1) && (hNumberOfCatches h1 == hNumberOfCatches h2) && (hID h1 > hID h2) = LT


instance Ord Prey where
    compare p1 p2
        | pEnergy p1 > pEnergy p2 = GT
        | pEnergy p1 < pEnergy p2 = LT
        | pEnergy p1 == pEnergy p2 && pID p1 < pID p2 = GT
        | pEnergy p1 == pEnergy p2 && pID p1 > pID p2 = LT


-- WRITE THE REST OF YOUR CODE HERE --

simulate :: [[Cell]] -> ([(Hunter,Coordinate)],[(Prey,Coordinate)])
simulate grid = (play grid ( (find_hunters grid (0,0) (length (grid!!0)) (length grid) []),(find_preys grid (0,0) (length (grid!!0)) (length grid) [] ) )  0   )

set_pEnergy :: Prey -> Int -> Prey
set_pEnergy prey1 new_en = Prey {pID= pID prey1 , pEnergy=new_en , pActions=pActions prey1}

delete_paction :: Prey -> Int -> Prey
delete_paction prey1 count = Prey {pID= pID prey1 , pEnergy=pEnergy prey1 , pActions= (drop count (pActions prey1))}

set_hEnergy :: Hunter -> Int -> Hunter
set_hEnergy hunter1 new_en = Hunter {hID=hID hunter1 , hlevel=hlevel hunter1 , hEnergy=new_en , hNumberOfCatches= hNumberOfCatches hunter1 , hActions = hActions hunter1} 

set_hEnCatch :: Hunter -> Int -> Int ->Hunter
set_hEnCatch hunter1 new_en new_catch 
    |new_en > 100 = Hunter {hID=hID hunter1 , hlevel=hlevel hunter1 , hEnergy=100 , hNumberOfCatches= new_catch , hActions = hActions hunter1}
    |otherwise = Hunter {hID=hID hunter1 , hlevel=hlevel hunter1 , hEnergy=new_en , hNumberOfCatches= new_catch , hActions = hActions hunter1} 

delete_haction :: Hunter -> Int -> Hunter
delete_haction hunter1 count = Hunter {hID=hID hunter1 , hlevel=hlevel hunter1 , hEnergy=hEnergy hunter1 , hNumberOfCatches= hNumberOfCatches hunter1 , hActions = (drop count (hActions hunter1))} 

c_act_h :: [(Hunter,Coordinate)] -> Int -> Int -> [(Hunter,Coordinate)]
c_act_h hunterlist del_count count 
    | count == (length hunterlist) = hunterlist
    | otherwise = (c_act_h (upd_hunter_list hunterlist (delete_haction (fst(hunterlist!!count)) del_count)  (snd(hunterlist!!count)) []) del_count (count+1))

c_act_p :: [(Prey,Coordinate)] -> Int -> Int -> [(Prey,Coordinate)]
c_act_p preylist del_count count 
    | count == (length preylist) = preylist
    | otherwise = (c_act_p (upd_prey_list preylist (delete_paction (fst(preylist!!count)) del_count)  (snd(preylist!!count)) []) del_count (count+1))

play :: [[Cell]] -> ([(Hunter,Coordinate)],[(Prey,Coordinate)]) -> Int -> ([(Hunter,Coordinate)],[(Prey,Coordinate)])
play grid (hunterlist,preylist) count
    |count==(length (hActions(fst(hunterlist!!0)))) || length(preylist)== 0 ={-(hunterlist,preylist)-}(reverse(sort(c_act_h hunterlist count 0)),(sort(c_act_p preylist count 0))) --count== # of hactions or preylist is empty then terminate
    |otherwise = (play grid (check grid ( (reverse(sort(move_hunt_list grid hunterlist 0 count))),(sort(move_prey_list grid preylist 0 count)) ) 0 0 0) (count+1) )


check :: [[Cell]] -> ([(Hunter,Coordinate)],[(Prey,Coordinate)]) -> Int -> Int -> Int ->  ([(Hunter,Coordinate)],[(Prey,Coordinate)])
check grid (hunterlist,preylist) c_hunt c_prey c_eat
    | c_hunt == (length hunterlist) =(hunterlist,preylist)
    | c_prey == (length preylist) = (check grid (hunterlist,preylist) (c_hunt+1) 0 0)
    | c_prey < (length preylist) && c_eat == 2  = (check grid (hunterlist,preylist) (c_hunt+1) 0 0)
    | c_prey < (length preylist) && c_eat < 2 && (snd(hunterlist!!c_hunt)) == (snd(preylist!!c_prey)) = (check grid ( (upd_hunter_list hunterlist (set_hEnCatch (fst(hunterlist!!c_hunt)) ( (hEnergy (fst(hunterlist!!c_hunt))) +20) ( (hNumberOfCatches (fst(hunterlist!!c_hunt))) +1) )  (snd(hunterlist!!c_hunt)) [] )  ,  (delete (preylist!!c_prey) preylist) ) c_hunt (c_prey+1) (c_eat+1) )
    | c_prey < (length preylist) && c_eat < 2 && (snd(hunterlist!!c_hunt)) /= (snd(preylist!!c_prey)) = (check grid (hunterlist,preylist) c_hunt (c_prey+1) c_eat)      
    |otherwise = (hunterlist,preylist)


move_hunt_list :: [[Cell]] -> [(Hunter,Coordinate)] -> Int -> Int -> [(Hunter,Coordinate)]
move_hunt_list grid hunterlist count index 
    | count == length hunterlist = hunterlist
    | otherwise = (move_hunt_list grid (moveHunter hunterlist grid count (cal_dir_hunter hunterlist count index) ) (count+1) index)

move_prey_list :: [[Cell]] -> [(Prey,Coordinate)] -> Int -> Int -> [(Prey,Coordinate)]
move_prey_list grid preylist count index 
    | count == length preylist = preylist
    | otherwise = (move_prey_list grid (movePrey preylist grid count (cal_dir_prey preylist count index) ) (count+1) index)


movePrey :: [(Prey,Coordinate)] -> [[Cell]] -> Int -> Coordinate  -> [(Prey,Coordinate)]
movePrey preylist grid index (a,b)
    |(pEnergy (fst(preylist!!index))) < 10 &&  ( is_in_trap grid ( fst(snd(preylist!!index)),snd(snd(preylist!!index)) ) )==False = (upd_prey_list preylist (set_pEnergy (fst(preylist!!index)) ( (pEnergy (fst(preylist!!index)))+1) ) (snd(preylist!!index)) [] )  --enerjisi yok trapte değil obs var mı yok mu fark etmiyor
    |(pEnergy (fst(preylist!!index))) < 10 && ( is_in_trap grid ( fst(snd(preylist!!index)),snd(snd(preylist!!index)) ) )==True = (upd_prey_list preylist (set_pEnergy (fst(preylist!!index)) 0) (snd(preylist!!index)) [] )         --  enerjisi yok , trapte
    |(is_in grid (a,b)) == False && (pEnergy (fst(preylist!!index))) > 10 && ( is_in_trap grid ( fst(snd(preylist!!index)),snd(snd(preylist!!index)) ) ) ==True = (upd_prey_list preylist (set_pEnergy (fst(preylist!!index)) ( (pEnergy (fst(preylist!!index)))-11) ) (snd(preylist!!index)) [] ) --içerde değil, enerjisi var , trapte
    |(is_in grid (a,b)) == False && (pEnergy (fst(preylist!!index))) == 10 && ( is_in_trap grid ( fst(snd(preylist!!index)),snd(snd(preylist!!index)) ) ) ==True = (upd_prey_list preylist (set_pEnergy (fst(preylist!!index)) 0 ) (snd(preylist!!index)) [] ) --içerde değil, enerjisi>10 , trapte
    |(is_in grid (a,b)) == False && ( is_in_trap grid ( fst(snd(preylist!!index)),snd(snd(preylist!!index)) ) )==False && (pEnergy (fst(preylist!!index))) > 9 = (upd_prey_list preylist (set_pEnergy (fst(preylist!!index)) ( (pEnergy (fst(preylist!!index)))-1) )  (snd(preylist!!index)) [] ) --içerde değil enerjisi==10 , trapte değil
    |(is_in grid (a,b)) == True  && (pEnergy (fst(preylist!!index))) > 10 && (grid!!b!!a)== X && ( is_in_trap grid ( fst(snd(preylist!!index)),snd(snd(preylist!!index)) ) )==True = (upd_prey_list preylist (set_pEnergy (fst(preylist!!index)) ( (pEnergy (fst(preylist!!index)))-11) ) (snd(preylist!!index)) [] ) --obs var şu an trapte enerjisi>10  aynı yerde kalacak
    |(is_in grid (a,b)) == True  && (pEnergy (fst(preylist!!index))) == 10 && (grid!!b!!a)== X && ( is_in_trap grid ( fst(snd(preylist!!index)),snd(snd(preylist!!index)) ) )==True = (upd_prey_list preylist (set_pEnergy (fst(preylist!!index)) 0 ) (snd(preylist!!index)) [] ) --obs var şu an trapte enerjisi=10  aynı yerde kalacak sonuçta enerjisi 0 olacak
    |(is_in grid (a,b)) == True && (pEnergy (fst(preylist!!index))) > 10 && (grid!!b!!a)/= X && ((grid!!b)!!a)== T = (upd_prey_list preylist (set_pEnergy (fst(preylist!!index)) ( (pEnergy (fst(preylist!!index)))-11) )    (a,b) [] ) --hareket ediyor trape doğru enerjisi > 10
    |(is_in grid (a,b)) == True && (pEnergy (fst(preylist!!index))) == 10 && (grid!!b!!a)/= X && (grid!!b!!a)== T = (upd_prey_list preylist (set_pEnergy (fst(preylist!!index)) 0 ) (a,b) [] ) --hareket ediyor trape doğru enerjisi=10
    |(is_in grid (a,b)) == True && (pEnergy (fst(preylist!!index))) > 9 && (grid!!b!!a)/= X && ((grid!!b)!!a)/= T = (upd_prey_list preylist (set_pEnergy (fst(preylist!!index)) ( (pEnergy (fst(preylist!!index)))-1) )   (a,b) [] ) --normal hareket ediyor
    |(is_in grid (a,b)) == True && (pEnergy (fst(preylist!!index))) > 9 && (grid!!b!!a)== X = (upd_prey_list preylist (set_pEnergy (fst(preylist!!index)) ( (pEnergy (fst(preylist!!index))) -1) )  (snd(preylist!!index)) [] ) --hareket edemiyor obs
    |(pEnergy (fst(preylist!!index))) < 10 && ( is_in_trap grid ( fst(snd(preylist!!index)),snd(snd(preylist!!index)) ) )==True =  (upd_prey_list preylist (set_pEnergy (fst(preylist!!index)) 0) (snd(preylist!!index)) [] )  --enerjisi yok trapin içinde 

moveHunter :: [(Hunter,Coordinate)] -> [[Cell]] -> Int -> Coordinate  -> [(Hunter,Coordinate)]
moveHunter hunterlist grid index (a,b)
    |(hEnergy (fst(hunterlist!!index))) < 10 =(upd_hunter_list hunterlist (set_hEnergy (fst(hunterlist!!index)) ( (hEnergy (fst(hunterlist!!index)))+1) ) (snd(hunterlist!!index)) [] )     --enerjisi yoksa 1 arttır her türlü aynı yerde
    |(is_in grid (a,b)) == True && (hEnergy (fst(hunterlist!!index))) > 9  && (grid!!b!!a)/= X = (upd_hunter_list hunterlist (set_hEnergy (fst(hunterlist!!index)) ( (hEnergy (fst(hunterlist!!index)))-1) ) (a,b) [] )     --,içerde , enerjisi var, obstacle yok 
    |(is_in grid (a,b)) == False && (hEnergy (fst(hunterlist!!index))) > 9 = (upd_hunter_list hunterlist (set_hEnergy (fst(hunterlist!!index)) ( (hEnergy (fst(hunterlist!!index))) -1) )  (snd(hunterlist!!index)) [] )   --enerjisi var, dışarda 
    |(is_in grid (a,b)) == True &&(hEnergy (fst(hunterlist!!index))) > 9  && (grid!!b!!a)== X = (upd_hunter_list hunterlist (set_hEnergy (fst(hunterlist!!index)) ( (hEnergy (fst(hunterlist!!index))) -1) )  (snd(hunterlist!!index)) [] )    -- içerde , obstacle var, enerjisi var-> enerjisi bir azalır


retP_first :: Cell -> Bool
retP_first (P x) = True
retP_first (x) = False

retP_sec :: Cell -> Prey
retP_sec (P x) = x


retH_first :: Cell -> Bool
retH_first (H x) = True
retH_first (x) = False

retH_sec :: Cell -> Hunter
retH_sec (H x) = x

upd_prey_list :: [(Prey,Coordinate)] -> Prey -> Coordinate ->  [(Prey,Coordinate)] -> [(Prey,Coordinate)]
upd_prey_list [] updated new_cord newlist = reverse newlist
upd_prey_list (x:xs) updated new_cord newlist
    | pID (fst x) == pID updated = (upd_prey_list xs updated new_cord  ((updated,new_cord):newlist) )
    | otherwise = (upd_prey_list xs updated new_cord (x:newlist))

upd_hunter_list :: [(Hunter,Coordinate)] -> Hunter -> Coordinate ->  [(Hunter,Coordinate)] -> [(Hunter,Coordinate)]
upd_hunter_list [] updated new_cord newlist = reverse newlist
upd_hunter_list (x:xs) updated new_cord newlist
    | hID (fst x) == hID updated = (upd_hunter_list xs updated new_cord  ((updated,new_cord):newlist) )
    | otherwise = (upd_hunter_list xs updated new_cord (x:newlist))


find_hunters :: [[Cell]] -> (Int,Int) -> Int -> Int -> [(Hunter,Coordinate)] -> [(Hunter,Coordinate)]
find_hunters grid (a,b) lenx leny l_hunter
    |b==leny = l_hunter
    |(retH_first ((grid!!b)!!a)) == True = if(a+1/=lenx) then (find_hunters grid (a+1, b) lenx leny ((retH_sec (grid!!b!!a),(a,b)):l_hunter)) 
                                        else (if(b<leny) then (find_hunters grid (0,b+1) lenx leny  ((retH_sec (grid!!b!!a),(a,b)):l_hunter)) else l_hunter)
    |(retH_first ((grid!!b)!!a)) == False = if(a+1/=lenx) then (find_hunters grid (a+1, b) lenx leny l_hunter ) 
                                        else (if(b<leny) then (find_hunters grid (0,b+1) lenx leny  l_hunter ) else l_hunter)

find_preys :: [[Cell]] -> (Int,Int) -> Int -> Int -> [(Prey,Coordinate)] -> [(Prey,Coordinate)]
find_preys grid (a,b) lenx leny l_prey 
    |b==leny = l_prey
    |(retP_first (grid!!b!!a)) == True = if(a+1/=lenx) then (find_preys grid (a+1, b) lenx leny ((retP_sec (grid!!b!!a),(a,b)):l_prey)) 
                                        else (if(b<leny) then (find_preys grid (0,b+1) lenx leny  ((retP_sec (grid!!b!!a),(a,b)):l_prey)) else l_prey)
    |(retP_first (grid!!b!!a)) == False = if(a+1/=lenx) then (find_preys grid (a+1, b) lenx leny l_prey ) 
                                        else (if(b<leny) then (find_preys grid (0,b+1) lenx leny  l_prey ) else l_prey)

cal_dir_prey :: [(Prey,Coordinate)] -> Int -> Int -> Coordinate
cal_dir_prey preylist p_index dir_index 
    | ((pActions (fst(preylist!!p_index)) )!!dir_index) == N = (fst(snd(preylist!!p_index)),(snd(snd(preylist!!p_index))-1))
    | ((pActions (fst(preylist!!p_index)) )!!dir_index) == S = (fst(snd(preylist!!p_index)),(snd(snd(preylist!!p_index))+1))
    | ((pActions (fst(preylist!!p_index)) )!!dir_index) == E = ((fst(snd(preylist!!p_index))+1),(snd(snd(preylist!!p_index))))
    | ((pActions (fst(preylist!!p_index)) )!!dir_index) == W = ((fst(snd(preylist!!p_index))-1),(snd(snd(preylist!!p_index))))

cal_dir_hunter :: [(Hunter,Coordinate)] -> Int -> Int -> Coordinate
cal_dir_hunter hunterlist h_index dir_index 
    | ((hActions (fst(hunterlist!!h_index)) )!!dir_index) == N = (fst(snd(hunterlist!!h_index)),(snd(snd(hunterlist!!h_index))-1))
    | ((hActions (fst(hunterlist!!h_index)) )!!dir_index) == S = (fst(snd(hunterlist!!h_index)),(snd(snd(hunterlist!!h_index))+1))
    | ((hActions (fst(hunterlist!!h_index)) )!!dir_index) == E = ((fst(snd(hunterlist!!h_index))+1),(snd(snd(hunterlist!!h_index))))
    | ((hActions (fst(hunterlist!!h_index)) )!!dir_index) == W = ((fst(snd(hunterlist!!h_index))-1),(snd(snd(hunterlist!!h_index))))


is_in_trap :: [[Cell]] -> Coordinate -> Bool
is_in_trap grid (a,b) 
    |(grid!!b)!!a == T = True
    |otherwise = False


is_in :: [[Cell]] ->  Coordinate -> Bool
is_in grid (a,b) 
    | (length grid) > b && (length (grid!!0)) > a && (a > -1) && (b > -1) = True --a->x , b->y 
    | otherwise = False



