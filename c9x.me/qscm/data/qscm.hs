-- Q scheme
--
import Control.Applicative
import Control.Monad
import Control.Monad.Reader
import Control.Monad.State
import Data.Char
import qualified Data.Map as M
import System.IO
import System.Environment

type Ident = String

data SExpr
    = ILit Int
    | SLit String
    | Idnt Ident
    | List [SExpr]

data Expr
    = EDef Ident Expr
    | EDo [Expr]
    | EIf Expr Expr Expr
    | ELet [(Ident, Expr)] Expr
    | ECall Expr [Expr]
    | EVar Ident
    | ELam [Ident] Expr
    | EILit Int
    | ESLit String

main :: IO ()
main = do
    args <- getArgs
    txt <- case args of
            [] -> hGetContents stdin
            f:_ -> readFile f
    case runStateT readSE txt of
        Nothing -> err "parse error"
        Just (se, _) ->
            case (vexpr se, args) of
                (Left e, _)   -> err e
                (Right p, []) -> evalProg p >>= putStrLn . showValue
		(Right p, _)  -> void (evalProg p)
  where
    err e = putStrLn $ "\x1b[31merror\x1b[0m: " ++ e
    evalProg p = runReaderT (runStateT (eval p) glo) []
    glo = Glo genv (M.singleton 0 (Str "" 0 False))
    genv = M.fromList
        [ ("+", VBlt plus)
        , ("-", VBlt minus)
        , ("*", VBlt mult)
        , ("/", VBlt idiv)
        , ("<", test "<" (<))
        , (">", test ">" (>))
        , ("<=", test "<=" (<=))
        , (">=", test ">=" (>=))
        , ("=", test "=" (==))
        , ("get", VBlt pget)
        , ("set", VBlt pset)
        , ("new", VBlt new)
        , ("cons", VBlt cons)
        , ("car", VBlt (access "car" fst))
        , ("cdr", VBlt (access "cdr" snd))
        , ("getc", VBlt getc)
        , ("putc", VBlt putc)
        ]


-- Language builtins

plus, minus, mult, pget, pset, new, cons, getc, putc :: [Value] -> ME Value

plus = foldM plusM (VInt 0)
  where
    plusM (VInt i) (VInt j)   = return (VInt $ i + j)
    plusM (VInt i) (VPtr b j) = return (VPtr b $ i + j)
    plusM (VPtr b i) (VInt j) = return (VPtr b $ i + j)
    plusM _ _                 = fail "invalid call to +"

minus (a:as) = foldM minusM a as
  where
    minusM (VInt i) (VInt j)   = return (VInt $ i - j)
    minusM (VPtr b i) (VInt j) = return (VPtr b $ i - j)
    minusM (VPtr b i) (VPtr c j)
        | b == c               = return (VInt $ i - j)
    minusM _ _                 = fail "invalid call to -"
minus _ = fail "wrong number of arguments in -"

mult = fmap VInt . foldM multM 1
  where
    multM i (VInt j) = return $ i * j
    multM _ _ = fail "integer expected in *"

idiv (a:as) = foldM divM a as
  where
    divM (VInt i) (VInt j) = return (VInt $ i `div` j)
    divM _        _        = fail "invalid call to /"
idiv _ = fail "wrong number of arguments in /"

pget [VPtr p off] = do
    so <- gets (M.lookup p . heap)
    case so of
        Just (Str s l _) | off < l -> return (VInt $ ord (s !! off))
        _ -> fail "invalid pointer in get"
pget _ = fail "invalid call to get"

pset [VPtr p off, VInt i] = do
    so <- gets (M.lookup p . heap)
    case so of
        Just (Str s l True) | off < l -> do
            let s' = take off s ++ [chr i] ++ drop (off+1) s
            modify (onheap $ M.insert p (Str s' l True))
            return (VInt i)
        _ -> fail "invalid pointer in set"
pset _ = fail "invalid call to set"

new [VInt n] = do
    modify (onheap $ allocStr True (replicate n ' '))
    blk <- gets (fst . M.findMax . heap)
    return $ VPtr blk 0
new _ = fail "invalid call to new"

cons [v1, v2] = return (VCns v1 v2)
cons _ = fail "invalid call to cons"

getc [] = do
    eof <- lift (lift isEOF)
    if eof
      then return (VInt 0)
      else (VInt . ord) <$> lift (lift getChar)
getc _ = fail "invalid call to getc"

putc [VInt n] = lift (lift (putChar (chr n))) >> return (VInt 0)
putc _ = fail "invalid call to putc"

access :: String -> ((Value, Value) -> Value) -> [Value] -> ME Value
access name f [VCns v1 v2] = return (f (v1, v2))
access name f _ = fail $ "invalid call to " ++ name

test :: String -> (Int -> Int -> Bool) -> Value
test name o = VBlt $ fmap (toi . all (uncurry o) . pairs) . ints
  where
    pairs (a : b : cs) = (b, a) : pairs (b : cs)
    pairs _ = []
    toi b = VInt $ if b then 1 else 0
    ints l = snd <$> foldM f (0, []) l
    f (b, is) (VPtr blk off)
        | blk == b || b == 0 = return (blk, off:is)
    f (b, is) (VInt i) = return (b, i:is)
    f (b, is) _ = fail $ "invalid call to " ++ name


-- Evaluator machinery

data Value
    = VInt Int
    | VCns Value Value
    | VPtr Int Int
    | VClo [Ident] Expr Env
    | VBlt ([Value] -> ME Value)

data Str = Str
    { string :: String
    , size :: Int
    , writeable :: Bool
    }

data Glo = Glo { genv :: Genv, heap :: Heap }
type Genv = M.Map Ident Value
type Heap = M.Map Int Str
type Env = [(Ident, Value)]

type ME = StateT Glo (ReaderT Env IO)

onheap :: (Heap -> Heap) -> Glo -> Glo
onheap f g = g { heap = f (heap g) }

allocStr :: Bool -> String -> Heap -> Heap
allocStr c s h =
    let str = Str s (length s) c in
    M.insert (fst (M.findMax h) + 1) str h

eval :: Expr -> ME Value

eval (EDef x e) = do
    v <- eval e
    modify (\g -> g { genv = M.insert x v (genv g) })
    return v

eval (EDo es) = do
    forM_ (init es) eval
    eval (last es)

eval (EIf etst eif eelse) = do
    vtst <- eval etst
    case vtst of
        VInt 0 -> eval eelse
        _      -> eval eif

eval (ELet bdgs bdy) = do
    -- | (i, e):bs <- bdgs = do
    --    v <- eval e
    --    local ([(i, v)] ++) $ eval (ELet bs bdy)
    -- | otherwise = eval bdy
    vs <- forM bdgs (eval . snd)
    local (zip (map fst bdgs) vs ++) $ eval bdy

eval (ECall ef eargs) = do
    vf <- eval ef
    vargs <- forM eargs eval
    case vf of
        VClo xs t e | length xs == length eargs ->
            local (const $ zip xs vargs ++ e) $ eval t
        VBlt f -> f vargs
        _ -> fail "illegal function call"

eval (EVar x) = do
    env <- ask
    glo <- gets genv
    case lookup x env <|> M.lookup x glo of
        Just v -> return v
        Nothing -> fail $ "unbound variable " ++ x

eval (ELam is bdy) = VClo is bdy <$> ask
eval (EILit i) = return $ VInt i
eval (ESLit s) = do
    modify (onheap $ allocStr False (s ++ "\NUL"))
    blk <- gets (fst . M.findMax . heap)
    return $ VPtr blk 0


-- Static tests (syntax only)

vexpr :: SExpr -> Either String Expr

vexpr (ILit i) = pure $ EILit i
vexpr (SLit s) = pure $ ESLit s
vexpr (Idnt i) = pure $ EVar i

vexpr (List [Idnt "def", Idnt idnt, bdy]) =
    EDef idnt <$> vexpr bdy
vexpr (List (Idnt "def" : _)) =
    Left "invalid definition"

vexpr (List (Idnt "do" : es)) | length es /= 0 =
    EDo <$> forM es vexpr
vexpr (List (Idnt "do" : _)) =
    Left "invalid empty do expression"

vexpr (List [Idnt "if", etst, eif, eelse]) =
    EIf <$> vexpr etst <*> vexpr eif <*> vexpr eelse
vexpr (List (Idnt "if" : _)) =
    Left "invalid if expression"

vexpr (List [Idnt "let", List bdgs, bdy]) =
    ELet <$> vbdgs bdgs <*> vexpr bdy
  where
    vbdgs (List [Idnt i, e] : bs) =
        (:) <$> (,) i <$> vexpr e <*> vbdgs bs
    vbdgs [] = return []
    vbdgs _ = Left "invalid binding"
vexpr (List [Idnt "let", Idnt var, bdg, bdy]) =
    ELet <$> ((: []) <$> (,) var <$> vexpr bdg) <*> vexpr bdy
vexpr (List (Idnt "let" : _)) =
    Left "invalid let binding"

vexpr (List [Idnt "fun", List vars, bdy]) =
    ELam <$> vvars vars <*> vexpr bdy
  where
    vvars (Idnt i : is) = (i:) <$> vvars is
    vvars [] = return []
    vvars _ = Left "ident expected in binding list"
vexpr (List (Idnt "fun" : _)) =
    Left "invalid function"

vexpr (List (ef : args)) =
    ECall <$> vexpr ef <*> forM args vexpr

vexpr (List []) =
    Left "invalid empty list"


-- Parsing

type MP = StateT String Maybe

getp :: (Char -> Bool) -> MP Char
getp p = do
    (c:cs) <- get
    guard $ p c
    put cs
    return c

readSE1 :: Char -> MP SExpr
readSE1 c =
    case c of
        '(' -> List <$> (many readSE <* closing ')')
        '"' -> SLit <$> (many readChr <* closing '"')
        '#' -> (ILit . ord) <$> getp (const True)
        _ | isDigit c -> ILit <$> readInt c
        _ | special c -> empty
        _ -> Idnt <$> readWord c
  where
    readInt c = do
        l <- (c:) <$> many (getp isDigit)
        return $ foldl (\a d -> a*10 + ord d - ord '0') 0 l
    readChr =
        getp (== '\\') *> (unescape <$> getp (const True)) <|>
        getp (/= '"')
    readWord c = (c:) <$> (many $ getp (not . special))
    special c = isSpace c || elem c "()\"#"
    unescape c =
        case c of
            'n' -> '\n'
            't' -> '\t'
            x   -> x
    closing c = space *> getp (== c)

readSE :: MP SExpr
readSE = (space *> getp (const True)) >>= readSE1

space :: MP String
space = many $ getp isSpace


-- Boring helpers

showValue (VInt i, _) = show i
showValue c@(VCns _ _, _) = "(" ++ seq c ++ ")"
  where
    seq (VCns v1 v2, g) = showValue (v1, g) ++ " " ++ seq (v2, g)
    seq x = showValue x
showValue (VPtr p off, g) =
    case M.lookup p (heap g) of
        Nothing -> "#wrongptr"
        Just (Str s l _)
            | off >= l -> "#wrongptr"
            | otherwise -> show (drop off s)
showValue (VClo xs _ _, _) = "#closure" ++ show xs
showValue (VBlt _, _) = "#builtin"
