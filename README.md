<!-- TODO - переписать на русском -->
# Язык программирования TomatoLang с ароматом эзотерики и привкусом безумия (WIP)

Это учебный проект, представляющий собой маленький Си-подобный язык программирования. Этот ЯП не преследует цели быть удобным/эффективным/в каком-либо ещё виде настоящим ЯП, т.к. иначе он бы превратился в маленькое подмножество Си или Python (смотря что считать "эффективностью"). Поэтому писать программы на этом ЯП тяжело, неудобно, но это не мешает получить базовые навыки создания компилятора, а отсутствие необходимости быть строгим позволяет добавить юмора и творчества. 

Этот репозиторий представляет собой вторую версию языка (первая находится в другом репо "Language"). Большая часть данного README перенесена оттуда, где оно было написано на англйиском (зачем? не знаю, спросите меня из прошлого), и на данный момент а) не переведена на русский, б) может быть неверной в некоторых деталях, но в общих чертах всё актуально и верно.

Прямо сейчас идёт работа над бэкендом, преобразующим AST в ассемблерный код (`NASM`). 

## Build

Repo includes Makefile. Build with `make` in order to build all three programs at once.
Also each program directory (frontend, middleend, backend) has its own Makefile.

NOTE: `tree` library is used in the project! You can find it in its own repo. The only place it is included in is `common\src\common.h`.

## Usage

The project is the compiler of the programming language, separated into three parts: `fronted`, `middleend` and `backend`.

1. `Frontend` takes `text file with program` and creates `compilator tree`.
2. `Middleend` does some work with the `compilator tree`, e.g. folding constants. (BUT: due to some specifics of the language, no simple optimizations with the compiler tree can be done).
3. `Backend` is currently absent, it is planned that it will create object files, compatible with GNU linker.
### Command line flags (common for all parts of the compiler)

1. `-h` - prints help.
2. `-i` - specifies input file.
3. `-o` - specifies output file.
4. `-l` - specifies log file.
5. `--img-dumps` - if specified, creates img of the AST.

When there is no corresponding flag, default configuration is used (see below).

### Return values (common for all parts of the compiler)

Please, see corresponding `*_statuses.h`.

### Compiler Frontend

Run `frontend` or `make run_front` from root folder.

Default configuration (all files are located in the root folder):

1. Input file: `prog.txt`.
2. Output file: `compiler_tree.txt`.
3. Log file: `stdout`.

#### Speicifc command line flags

1. `--img-dumps` - turns on image dumps and specifies folder for this dumps.

### Compiler Middleend

Run `middleend` or `make run_middle` from root folder.

Default configuration (all files are located in the root folder):

1. Input file: `compiler_tree.txt`.
2. Output file: `compiler_tree_new.txt`.
3. Log file: `stdout`.

### Compiler Backend (ABSENT CURRENTLY)

Run `backend.exe` or `make run_back` (sometimes doesn't work propely, I really don't know why <!-- TODO -->) from root folder.

Default configuration (all files are located in the root folder):

1. Input file: `compiler_tree.txt`.
2. Output file: `asm.txt`.
3. Log file: `stdout`.

## Programming language description

### Main idea

Programs written in this programming language try to look like crazy recipes of some crazy dish. "Crazy" means that there is no list of ingredients in the beginning, or some other common sense things, which one can usually find in real-life recipes. So, the programmer plays the role of the author of a recipe, and the processor - of the chef, who is going to cook it. That's why most of the verbs in the text of the program must be read in the imperative mood.

### Some notes and details

1. All space symbols are ignored, new line symbols also don't matter, but they separate keywords and other constructions from each other.
2. Everything surrounded by single `#` is considered a comment and is ignored, e.g. `Quickly Obtain #comment# 10 Units Of Milk!`.

### Grammar

Note:

1. Terminal symbols and keywords are surrounded with qoutes `""`, non-terminal symbols are written as is.
2. `+` means `one or more`.
3. `*` means `zero or more`.
4. `?...?` means some special case.
5. `<...>` means something connected with context.
6. `{...}` means something which is not obligatory.

```py
Prog            ::= "ProgStart" { FuncDefs } Operators "ProgEnd"
FuncDefs        ::= "FuncDefsStart" FuncDef+ "FuncDefsEnd"
FuncDef         ::= FuncRecipe | FuncAction
FuncRecipe      ::= "FuncRecipeHeader" Id {"Using" FormalArgs "AsIngr"} "Colon" Operators
FuncAction      ::= "FuncActionHeader" Id {"Using" FormalArgs "AsIngr"} "Colon" Operators
FormalArgs      ::= Id<Var> ( "Comma" Id<Var> )*
FactArgs        ::= Expr ( "Comma" Expr )*
Operators       ::= Op+
Op              ::= VarBirth | VarDeath | Assign | If | While | Return<in FuncRecipe> | CallFuncAction | PrintNum | PrintStr
PrintStr        ::= "PrintStr" ?string in quotes? "Dot"
PrintNum        ::= "PrintNum" Id<Var> "Dot"
Return          ::= "Return1" Expr "Return2"
VarBirth        ::= "VarBirthOp" Num "UnitsOf" Id "Dot"
VarDeath        ::= "VarDeathOp" Id<Var> "Dot"
Assign          ::= "Asgn1" Expr "Asgn2" Id<Var> "Dot"
Expr            ::= Mulive ( ?Amp (group)? ("OpAdd" | "OpSub") Mulive )*
Mulive          ::= Unr ( ?Amp (group)? ( "OpMul" | "OpDiv" ) Unr )*
Unr             ::= ( ?Amp (group)? ?UnrOp (group)? Ingr ) | Ingr
Ingr            ::= ( Num "UnitsOf" Primal ) | Primal
Primal          ::= ("InBracketsStart" Expr "Semicolon") | CallFuncRecipe | Id<Var>
Id              ::= ['a'-'z','A'-'Z']['a'-'z','A'-'Z','_','0'-'9']*
Num             ::= ( "InputOp" ) | ( ?float number? )
If              ::= "If1" "Cond" ?CmpOp (group)? Expr "CmpWith" Expr "If2" Operators { "Else" Operators } "IfEnd"
While           ::= "While1" "Cond" ?CmpOp (group)? Expr "CmpWith" Expr "While2" Operators "WhileEnd"
CallFuncRecipe  ::= "CallFuncRecipe" Id<func> {"BracketOpn" "Using" FactArgs "AsIngr" "BracketCls"}
CallFuncAction  ::= "CallFuncAction" Id<func> {"BracketOpn" "Using" FactArgs "AsIngr" "BracketCls"} "Dot"
```

### Keywords

|Designation in grammar|Designation in program|Comment
|-|-|-|
|Amp_10|Fanatically|
|Amp_1|Angrily|
|Amp_2|Unfortunately|
|Amp_3|Madly|
|Amp_4|Thickly|
|Amp_5|Rapidly|
|Amp_6|Hastily|
|Amp_7|Emotionally|
|Amp_8|Desperately|
|Amp_9|Fiercely|
|AsIngr|As Ingredients|
|Asgn1|Place|
|Asgn2|Right Into|
|CallFuncAction|Perform|
|CallFuncRecipe|Cooked Beforehand|
|CmpOp_equal|Just The Same Amount Of|
|CmpOp_lessOrEqual|The Same Amount Or Less Of|
|CmpOp_less|Less|
|CmpOp_moreOrEqual|The Same Amount Or More Of|
|CmpOp_more|More|
|CmpOp_notEqual|Not The Same Amount Of|
|CmpWith|Comparing With|
|Cond|There Happens To Be|
|Else|Otherwise You Should Do A Completely Different Thing:|
|FuncActionHeader|Skill To Do|
|FuncDefsEnd|Here Is The Recipe Itself:|
|FuncDefsStart|Here Are Some Skills You Need To Have:|
|FuncRecipeHeader|Skill To Cook|
|If1|In Case|
|If2|Urgently Do The Following Steps:|
|IfEnd|Now, Breathe Out And Continue Whatever You Were Doing!|
|InBracketsStart|The Following Prepared Beforehand:|
|InputOp|As Much As The Universe Says|
|OpAdd|Mixed With|
|OpDiv|Spread On|
|OpMul|Fried With|
|OpSub|Without|
|PrintNum|Serve|
|PrintStr|Scream In Despair:|
|ProgEnd|That's All! Don't Forget To Check It On Your Friends Before Tasting Yourself!|
|ProgStart|The Recipe Of The Most Delicious Dish One Can Ever Imagine!|
|Return1|There Is No Time To Explain, Use|
|Return2|As The Result Of This Skill!|
|UnitsOf|Units Of|
|UnrOp_cos|Diced|
|UnrOp_exp|Grated|
|UnrOp_ln|Squeezed|
|UnrOp_minus|Rinsed|
|UnrOp_sin|Sliced|
|UnrOp_sqrt|Peeled|
|Using|Using|
|VarBirthOp|Quickly Obtain|
|VarDeathOp|Throw Away|
|While1|As Long As|
|While2|Repeat The Following:|
|WhileEnd|Repeat Until Ready And Then Go Further!|

<!-- TODO - идея для continue: "закроем глаза на то, что в этой итерации ты схалтурил. Просто переходи к следующей, но не забывай, что Большой Брат следит за тобой." -->
<!-- TODO - идея для break:    "давай будем честны, тебе это надоело. Просто бросай все эти повторения и не возвращайся к ним больше, иди дальше." -->

### Separating symbols

|Designation in grammar|Designation in program|Comment|
|-|-|-|
|Dot|!|
|Semicolon|;|
|Colon|:|
|Comma|,|
|BracketOpn|(|
|BracketCls|)|

### Program examples

- Factorial:

```
The Recipe Of The Most Delicious Dish One Can Ever Imagine!

Here Are Some Skills You Need To Have:

Skill To Cook Factorial Using Mathematicians As Ingredients:
    Quickly Obtain 1 Units Of Math!

    In Case There Happens To Be Just The Same Amount Of Mathematicians
    Comparing With Math Urgently Do The Following Steps:
        There Is No Time To Explain, Use Math As The Result Of This Skill!
    Now, Breathe Out And Continue Whatever You Were Doing!

    There Is No Time To Explain, Use Mathematicians Angrily Fried With Cooked Beforehand
    Factorial (Using Mathematicians Unfortunately Without Math As Ingredients)
    As The Result Of This Skill!

Here Is The Recipe Itself:
Quickly Obtain As Much As The Universe Says Units Of Mathematicians!
Quickly Obtain 0 Units Of Answer!

In Case There Happens To Be Just The Same Amount Of Mathematicians
Comparing With Answer Urgently Do The Following Steps:
    Quickly Obtain 1 Units Of TheOne!
    Place TheOne Right Into Answer!
Otherwise You Should Do A Completely Different Thing:
    Place Cooked Beforehand Factorial (Using Mathematicians As Ingredients) Right Into Answer!
Now, Breathe Out And Continue Whatever You Were Doing!
Serve Answer!

That's All! Don't Forget To Check It On Your Friends Before Tasting Yourself!
```

AST (is generated if `--img_dumps` is specified):
![](readme_imgs/factorial.jpg)

---

- Quadratic equation solver:

```
The Recipe Of The Most Delicious Dish One Can Ever Imagine!

Here Are Some Skills You Need To Have:

Skill To Cook Discriminant Using Apples, Beetroots, Carrots As Ingredients:
    Quickly Obtain 0 Units Of Discr!
    Place Beetroots Angrily Fried With Beetroots Unfortunately Without
    4 Units Of Apples Madly Fried With Carrots Right Into Discr!

    There Is No Time To Explain, Use Discr As The Result Of This Skill!

# ax + b = 0, a != 0 #
Skill To Cook LinearRoot Using Aubergines, Beans As Ingredients:
    Quickly Obtain 0 Units Of Result!
    Place Emotionally Rinsed Beans Thickly Spread On Aubergines Right Into Result!

    There Is No Time To Explain, Use Result As The Result Of This Skill!

# ax + b = 0 #
Skill To Do SolvationOfLinear Using Aubergines, Beans As Ingredients:
    Quickly Obtain 0 Units Of Nothing!
    In Case There Happens To Be Just The Same Amount Of Aubergines
    Comparing With Nothing Urgently Do The Following Steps:
        In Case There Happens To Be Just The Same Amount Of Beans
        Comparing With Nothing Urgently Do The Following Steps:
            Scream In Despair: "Well, there is kinda the whole infinity and a small carriage of roots..."!
        Otherwise You Should Do A Completely Different Thing:
            Scream In Despair: "Quite interesting, that's also not a linear equation."!
            Scream In Despair: "It's not an equation at all: there are simply no roots, even imaginary ones!"!
        Now, Breathe Out And Continue Whatever You Were Doing!
    Otherwise You Should Do A Completely Different Thing:
        Quickly Obtain 0 Units Of Root!
        Place Cooked Beforehand LinearRoot (Using Aubergines, Beans As Ingredients)
        Right Into Root!
        Scream In Despair: "Here is the only linear root:"!
        Serve Root!
    Now, Breathe Out And Continue Whatever You Were Doing!

Skill To Cook QuadraticFirstRoot Using Apples, Beetroots, Dicsr As Ingredients:
    Quickly Obtain 0 Units Of Result!
    Place The Following Prepared Beforehand: Madly Rinsed Beetroots Fiercely
    Mixed With Hastily Peeled Dicsr; Thickly Spread On The Following Prepared Beforehand:
    2 Units Of Apples; Right Into Result!

    There Is No Time To Explain, Use Result As The Result Of This Skill!

Skill To Cook QuadraticNumberOfRoots Using Dicsr As Ingredients:
    Quickly Obtain 0 Units Of Result!
    Quickly Obtain 1 Units Of Neutral!
    Quickly Obtain 0 Units Of Nothing!
    In Case There Happens To Be More Dicsr
    Comparing With Nothing Urgently Do The Following Steps:
        Place 2 Units Of Neutral Right Into Result!
        There Is No Time To Explain, Use Result As The Result Of This Skill!
    Now, Breathe Out And Continue Whatever You Were Doing!

    In Case There Happens To Be Just The Same Amount Of Dicsr
    Comparing With Nothing Urgently Do The Following Steps:
        Place 1 Units Of Neutral Right Into Result!
        There Is No Time To Explain, Use Result As The Result Of This Skill!
    Now, Breathe Out And Continue Whatever You Were Doing!

    In Case There Happens To Be Less Dicsr
    Comparing With Nothing Urgently Do The Following Steps:
        Place 0 Units Of Neutral Right Into Result!
        There Is No Time To Explain, Use Result As The Result Of This Skill!
    Now, Breathe Out And Continue Whatever You Were Doing!

# ax^2 + bx + c = 0 #
Skill To Do SolvationOfQuadratic Using Apples, Beetroots, Carrots As Ingredients:
    Quickly Obtain 0 Units Of Nothing!
    Quickly Obtain 1 Units Of Neutral!
    In Case There Happens To Be Just The Same Amount Of Apples
    Comparing With Nothing Urgently Do The Following Steps:
        Scream In Despair: "Well, that's not quite a quadratic equation, "!
        Scream In Despair: "smells more like a linear one. Anyway..."!
        Perform SolvationOfLinear (Using Beetroots, Carrots As Ingredients)!
    Otherwise You Should Do A Completely Different Thing:
        Quickly Obtain 0 Units Of Discr!
        Place Cooked Beforehand Discriminant (Using Apples, Beetroots, Carrots As Ingredients)
        Right Into Discr!
        Scream In Despair: "Here is the discriminant of your equation:"!
        Serve Discr!

        Quickly Obtain 0 Units Of NumOfRoots!
        Place Cooked Beforehand QuadraticNumberOfRoots (Using Discr As Ingredients)
        Right Into NumOfRoots!
        Scream In Despair: "The number of roots is:"!
        Serve NumOfRoots!

        In Case There Happens To Be Just The Same Amount Of NumOfRoots
        Comparing With Nothing Urgently Do The Following Steps:
            Scream In Despair: "No real roots!"!
        Otherwise You Should Do A Completely Different Thing:
            Quickly Obtain 0 Units Of FirstRoot!
            Place Cooked Beforehand QuadraticFirstRoot (Using Apples, Beetroots, Discr As Ingredients)
            Right Into FirstRoot!
            Scream In Despair: "Aaaand here is the first root:"!
            Serve FirstRoot!

            In Case There Happens To Be Just The Same Amount Of NumOfRoots
            Comparing With 2 Units Of Neutral Urgently Do The Following Steps:
                Quickly Obtain 0 Units Of SecondRoot!
                Place Angrily Rinsed Beetroots Hastily Spread On Apples Unfortunately
                Without FirstRoot Right Into SecondRoot!
                Scream In Despair: "And the second root is:"!
                Serve SecondRoot!
            Now, Breathe Out And Continue Whatever You Were Doing!
        Now, Breathe Out And Continue Whatever You Were Doing!
    Now, Breathe Out And Continue Whatever You Were Doing!

Here Is The Recipe Itself:

Quickly Obtain 1 Units Of Neutral!
Quickly Obtain 0 Units Of Nothing!

Scream In Despair: "Hi, I can solve quadratic equations, like ax^2 + bx + c = 0!"!
Scream In Despair: "Do you want to make a try? [1/0]"!

Quickly Obtain As Much As The Universe Says Units Of Ans!
As Long As There Happens To Be Not The Same Amount Of Ans Comparing With
Nothing Repeat The Following:
    Scream In Despair: "Please, enter coefficient a:"!
    Quickly Obtain As Much As The Universe Says Units Of Apples!

    Scream In Despair: "Please, enter coefficient b:"!
    Quickly Obtain As Much As The Universe Says Units Of Beetroots!

    Scream In Despair: "Please, enter coefficient c:"!
    Quickly Obtain As Much As The Universe Says Units Of Carrots!

    Scream In Despair: "Here are the entered coefficients:"!
    Serve Apples!
    Serve Beetroots!
    Serve Carrots!

    Perform SolvationOfQuadratic (Using Apples, Beetroots, Carrots As Ingredients)!

    Scream In Despair: "Done! Do you want to solve another equation? [1/0]"!
    Place As Much As The Universe Says Units Of Neutral Right Into Ans!

    Throw Away Apples!
    Throw Away Beetroots!
    Throw Away Carrots!
Repeat Until Ready And Then Go Further!

Scream In Despair: "Goodbye!"!

That's All! Don't Forget To Check It On Your Friends Before Tasting Yourself!
```

AST (is generated if `--img_dumps` is specified):

![](readme_imgs/quadratic.jpg)