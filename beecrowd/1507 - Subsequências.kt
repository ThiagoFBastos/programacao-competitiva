import java.util.*

fun isSubsequence(string: String, subsequence: String): Boolean {
    var i = 0
    val length = subsequence.length

    for (c in string) {
        if (c == subsequence[i]) {
            i += 1

            if(i == length) {
                break
            }
        }
    }

    return i == length
}

fun main(args: Array<String>) {

    val sc = Scanner(System.`in`)

    sc.useLocale(Locale.US)

    val tc = sc.nextInt()

    for (i in 0 until tc) {
        val target = sc.next()

        val queries = sc.nextInt()

        for (j in 0 until queries) {
            val candidate = sc.next()

            if (isSubsequence(target, candidate)) {
                println("Yes")
            } else {
                println("No")
            }
        }
    }
}