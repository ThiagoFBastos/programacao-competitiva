import java.util.*

fun calculaTempo(horaInicio: Int, minutoInicio: Int, horaFinal: Int, minutoFinal: Int): Pair<Int, Int> {
    val diaEmMinutos = 24 * 60
    val tempoIniciaialMinutos = 60 * horaInicio + minutoInicio
    val tempoFinalMinutos = 60 * horaFinal + minutoFinal

    var minutos = if(tempoIniciaialMinutos < tempoFinalMinutos) {
        tempoFinalMinutos - tempoIniciaialMinutos
    } else {
        diaEmMinutos - tempoIniciaialMinutos + tempoFinalMinutos
    }

    val horas = minutos / 60

    minutos %= 60

    return Pair<Int, Int>(horas, minutos)
}

fun main(args: Array<String>) {

    val sc = Scanner(System.`in`)

    sc.useLocale(Locale.US)

    val horaInicio = sc.nextInt()
    val minutoInicio = sc.nextInt()
    val horaFinal = sc.nextInt()
    val minutoFinal = sc.nextInt()

    val (horas, minutos) = calculaTempo(horaInicio, minutoInicio, horaFinal, minutoFinal)

    println("O JOGO DUROU $horas HORA(S) E $minutos MINUTO(S)")
}