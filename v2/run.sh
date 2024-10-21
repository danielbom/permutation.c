function run () {
    EXE=output/einstein
    OUT=output/.current
    TMS=output/times.txt
    TIMEIT=0
    OPTIMIZE=0
    CHECK=0
    SILENT=0
    DEBUG=0

    for arg in $@
    do
        case "$arg" in
        ("-O") OPTIMIZE=1 ;;
        ("-c")    CHECK=1 ;;
        ("-s")   SILENT=1 ;;
        ("-d")    DEBUG=1 ;;
        ("-t")   TIMEIT=1 ;;
        ("*")  echo "Unknown argument: $arg" ;;
        esac
    done

    if [ $DEBUG = 1 ]
    then
        set -x
    fi

    if [ $SILENT = 0 ]
    then
        function log () {
            echo $*
        }
    else
        function log () {
            :
        }
    fi

    log "Testing: $1"

    GCC_ARGS=("$1")
    GCC_VARGS=("Compilation ")
    if [ $OPTIMIZE = 1 ]
    then
        GCC_VARGS+="[x] optimization "
        GCC_ARGS+=("-O3")
    else
        GCC_VARGS+="[ ] optimization "
    fi

    if [ $TIMEIT = 1 ]
    then
        GCC_VARGS+="[x] time it "
        GCC_ARGS+=("-DTIME_IT")
    else
        GCC_VARGS+="[ ] time it "
    fi

    log "${GCC_VARGS[@]}"
    log gcc ${GCC_ARGS[@]} -o $EXE
    gcc ${GCC_ARGS[@]} -o $EXE -Wall -Wextra

    ./$EXE > $OUT

    if [ $TIMEIT = 1 ]
    then
        TIME_SPENT=$(grep -e "Time" output/.current)
        echo "OPTIMIZE=$OPTIMIZE $1: $TIME_SPENT" >> $TMS
    fi

    if [ $CHECK = 1 ]
    then 
        ok=`diff $OUT expected-output.txt`
        if [ ! -z "$ok" ]
        then
            echo "$1: Check NOT OK"
            exit 1
        else
            echo "$1: Check OK"
        fi
    fi

    rm $EXE $OUT
    echo ""
}

mkdir output -p

run einstein-problem-functions.c -s -c
run einstein-problem-macros.c -s -c
run einstein-problem-merge.c -s -c
run einstein-problem-pure.c -s -c

run einstein-problem-functions.c -t
run einstein-problem-macros.c -t
run einstein-problem-merge.c -t
run einstein-problem-pure.c -t

run einstein-problem-functions.c -t -O
run einstein-problem-macros.c -t -O
run einstein-problem-merge.c -t -O
run einstein-problem-pure.c -t -O
