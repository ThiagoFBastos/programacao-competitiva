import java.util.*

fun main(args: Array<String>) {

    val sc = Scanner(System.`in`)

    sc.useLocale(Locale.US)

    var n = sc.nextLong()
    var divisors = 1L;
    var prime_divisors = 1L
    var p = 2L

    while (p * p <= n) {
        if(n % p == 0L) {
            divisors *= 2L
            ++prime_divisors
            do {
                n /= p;
            } while(n % p == 0L)
        }

        ++p;
    }

    if (n > 1L) {
        ++prime_divisors
        divisors *= 2L
    }

    divisors -= prime_divisors

    println(divisors)
}