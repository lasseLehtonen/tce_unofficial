import QtQuick 2.0

Rectangle {
    id: core
    color: printed.color_bg

    signal redraw
    onRedraw: canvas.requestPaint()

    Canvas {
        id: canvas
        anchors.fill: parent
        onPaint: {
            canvas.update()
            var ctx = canvas.getContext('2d');
            var h = canvas.height
            var w = canvas.width
            var lw = ctx.lineWidth

            // Draw
            ctx.beginPath()
            ctx.clearRect(0, 0, canvas.width, canvas.height);
            ctx.strokeStyle = printed.color_signal
            ctx.lineWidth = printed.signalWidth
            ctx.moveTo(w*0/8, h*4/4)
            ctx.lineTo(w*2/8, h*4/4)
            ctx.lineTo(w*2/8, h*0/4)
            ctx.lineTo(w*6/8, h*0/4)
            ctx.lineTo(w*6/8, h*4/4)
            ctx.lineTo(w*8/8, h*4/4)
            ctx.stroke()
        }
    }
}
