import java.util.*

fun main(args: Array<String>) {

    val sc = Scanner(System.`in`)

    sc.useLocale(Locale.US)

    val l = sc.nextLong()
    val r = sc.nextLong()

    val sum = (l + r) * (r - l + 1) / 2

    println(sum)
}