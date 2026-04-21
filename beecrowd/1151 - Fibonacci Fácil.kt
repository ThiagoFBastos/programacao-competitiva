import java.util.*

fun main(args: Array<String>) {

    val sc = Scanner(System.`in`)

    sc.useLocale(Locale.US)

    val n = sc.nextInt()

    if(n == 1) {
        println(0)
        return
    } else if(n == 2) {
        println("0 1")
        return
    }

    val fibonacci = LongArray(n)

    fibonacci[0] = 0
    fibonacci[1] = 1

    for(i in 2 until n) {
        fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2]
    }

    for(i in 0 until n) {
        val value = fibonacci[i]
        print("$value")

        if(i < n - 1) {
            print(" ")
        } else {
            print("\n")
        }
    }
}