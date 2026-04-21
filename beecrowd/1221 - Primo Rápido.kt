import java.util.*

fun getPrimeNumbers(maxn: Int): ArrayList<Int> {
    val primeNumbers = ArrayList<Int>()
    val isPrime = BooleanArray(maxn)

    isPrime.fill(true)

    var i = 2

    while(i * i <= maxn) {
        if(isPrime[i]) {
            for (j in 2 * i  until maxn step i) {
                isPrime[j] = false
            }
        }

        i += 1
    }

    for(i in 2 until maxn) {
        if(isPrime[i]) {
            primeNumbers.add(i)
        }
    }

    return primeNumbers
}

fun isPrime(num: Int, primeNumbers: ArrayList<Int>): Boolean {

    for(value in primeNumbers) {
        if(value * value > num) {
            break
        } else if(num % value == 0) {
            return false
        }
    }

    return num > 1
}

fun main(args: Array<String>) {

    val sc = Scanner(System.`in`)

    sc.useLocale(Locale.US)

    val maxn = 46341
    val primeNumbers = getPrimeNumbers(maxn)

    val tc = sc.nextInt()

    for(i in 1..tc) {
        val value = sc.nextInt()

        if(isPrime(value, primeNumbers)) {
            println("Prime")
        } else {
            println("Not Prime")
        }
    }
}