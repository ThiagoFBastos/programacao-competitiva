import java.util.*


fun main(args: Array<String>) {

    var dinheiro = readLine()!!.toInt()

    val cedulas = arrayOf(100, 50, 20, 10, 5, 2, 1)

    println(dinheiro)

    for (cedula in cedulas) {
        val quantidade = dinheiro / cedula

        dinheiro %= cedula

        println("$quantidade nota(s) de R$ $cedula,00")
    }
}