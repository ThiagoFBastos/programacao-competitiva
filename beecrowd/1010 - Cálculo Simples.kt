import java.util.*

class Tool {
    private var id: Int? = null;
    private var count: Int? = null;
    private var cost: Double? = null;

    fun Read() {
        val line = readLine()!!
        val elements = line.split(" ")

        this.id = elements[0].toInt()
        this.count = elements[1].toInt()
        this.cost = elements[2].toDouble()
    }

    fun TotalPrice(): Double {
        return this.count!! * this.cost!!
    }
}

fun main(args: Array<String>) {

    val firstTool = Tool();
    val secondTool = Tool();

    firstTool.Read()
    secondTool.Read()

    val totalPrice = firstTool.TotalPrice() + secondTool.TotalPrice()

    println("VALOR A PAGAR: R$ %.2f".format(Locale.US, totalPrice))
}