import java.util.*

fun main(args: Array<String>) {

    val sc = Scanner(System.`in`)

    sc.useLocale(Locale.US)

    while (sc.hasNext()) {
        val n = sc.nextInt()

        val frequency = IntArray(102)

        for (i in 0 until n) {
            val l = sc.nextInt()
            val r = sc.nextInt()

            ++frequency[l];
            --frequency[r + 1];
        }

        val num = sc.nextInt()

        for (i in 1..num) {
            frequency[i] += frequency[i - 1]
        }

        val count = frequency[num]

        if (count == 0) {
            println("$num not found")
        } else {
            var l = 0

            for(i in 1 until num) {
                l += frequency[i]
            }

            val r = l + count - 1

            println("$num found from $l to $r")
        }
    }
}