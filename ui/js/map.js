var colors = {
    '0': 'rgba(0, 150, 255, 0.75)',
    '1': 'rgba(255, 0, 255, 0.75)',
    '2': 'rgba(255, 255, 0, 0.75)',
    '3': 'rgba(0, 255, 255, 0.75)',
    '4': 'rgba(150, 200, 0, 0.75)',
    '5': 'rgba(255, 150, 255, 0.75)',
    '6': 'rgba(255, 255, 255, 0.75)',
    '7': 'rgba(150, 100, 255, 0.75)',
    '8': 'rgba(50, 150, 50, 0.75)'
};

var style = {
    'nodeColor': 'rgba(255, 255, 0, 0.25)',
    'edgeColor': 'rgba(255, 50, 0, 0.25)',
    'routeColor': 'rgba(0, 150, 255, 0.75)'
};

var icons = {
    purple: "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAABmJLR0QAAAAAAAD5Q7t/AAAACXBIWXMAAA7EAAAOxAGVKw4bAAAAB3RJTUUH5AIYDwE4lCkRxgAABQBJREFUeNrVm31oV1UYxz+/3xIpFWLmbGXNFqVmhDoolmVFQUEjcNqLkIlkcvxDyGumaG9iqAs6RBEcorS3v6zYYutlkURLW81BBVZuZVjNNG3aiyNJp/1xn4EIq99z7zn3d/3++fudl+f53Ofc+5zn3FsgA0W4SuAGYCZwBVALVAGjpMkAcADYDXwLbAM+tpjDoW0rBHT6bOBO4D7gJqCoHGIQ+Ah4FXjTYv4+IwBEuFHAUmCZXGUf+hWwwPMWM5BbABGuEXgGuChQYP0IPGgxLbkCIOH+LLCIbPQasMRHNBQ8OF8DvAdMIVvtBG63mJ/KBiDCTQXagQspj/qAWy3mm8wBRLhaeVxVU179Asy0mD2ZAYhw5wJdwGXkQz3ANRbzh7ZjMeGEL+XIeYBJwItJOhYTXP37gUbyp7kRbkHQJRDhxkq4jU1h6EngS+A7YJ/8Vi0RNS3ljfkAMFmTQp+lnOCRFM7vB5okre0bBvAESZ9XAuMTzFEFrAZWeI+ACDcO2AOcozTqBLARWF9q4hLhRgvshxNExBFgosX0+46AxQmcHwDmW0yzppPFHAFWRbgdshnSzDtabN3g+yZ4b4IrP0/r/Gkg3gLmyM5Qo/lenwIRbhowWWnEaotpTXtrt5j3gSeU3aZEuKt8RsAtSgN6ZfvqS03y1NDoZp8ArldO/pjFHPPlvYyljYJZPgFcqbwLvx0g0WmWm2qpmuoFQIQbCdQoJm63mKO+vZeS2AeKLpdEuBE+IqASqFDu00PWADRJXqUPAGOURu4LCEA79hgfALSZ2NGAALSV4QofAPqVk4YskFygbP+bDwCHJasrVTUBAWjGPgH8nhqAxQwq195tITyPcAXl2HvFdi95QLdi4okRbkYABnXAxYr2JdlcKoAdSmPXBADwqLJ9l08Anyonnx3hrvMY/jcCdyi7dfoEsA04pJi8AGyRCk9a56uB15Xd+oHt3gDIZuTdBI/DlghXlcL58UAb+oOXVos57rsgkqSwUQd0RbjpCZyvk3Wc5IZasq2aklgbcdVVe0VrBMJmYK3F7P0fxycAjwMLlXuQIe0nPqssea1qrspG4optUg3K2nwH2EV87g9wPvHhRgNwbULHh7TeYtaEiACAF4hLzklPlCqkUDGLMDoJbNJ0UDliMT8AreRXzRazOxiAoRDLMYAN2g5qABbTBXyYQ+fbLaY7OADRuhwCSGRTIgAW0yGPxbyoxWK2ZwZAtAI4ngPnB4nPEckUgMXsAl7JAYBNFvN15gBEK4GDZXS+P+3WOxUAOYJeVUYAyy3mYNkAiDYTv9ObtT4hPjpPJV9vik4CvgJGZuT8P8D0NO8H+owALKYHeDrDq/+UD+e9ARA9Sfy+f2h97zMd9wZADi8XoH+bQ6MTwCKf3w5U+LSuk7af62kYEXC7u85iXvY5YDGAkWuBzwKM2y3LzKuCfDIT4S4FvkB/sjycBoAZFtPr29YQEYAUJZZ7HHJpCOeDRcApkfAGMDflMFss5u5QNhYJq4XEn8ElVS/wQEgDgwKQNz5nA38lXPeNFvPnGQvglCxxcYKuS9Jsc8uSB/xHfrCznoZxwNUldnnOYpqysK1IdloGbC2hXQfwUFZGFTIEMPQNcSdw+TBNeoD6LL4ZLgsAgVALfA6cd9pfh8T53iztKWYNQE6X5siefkjHgLuydr4sAARCBzCP+MPHPuAei9laDlv+BZfFQHYG++M9AAAAAElFTkSuQmCC",
    pink: "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAABmJLR0QA/wD/AP+gvaeTAAAACXBIWXMAAA7EAAAOxAGVKw4bAAAAB3RJTUUH5AIdDwkEREEXewAABQBJREFUeNrVm12IVVUUx3/7TiGlQow1NmWNTeRHRqjzEGVZUVBQBI5mCZlItsEHITFTtC9JHA2KKHxZlFL2EFbMxGg1kYSTZo0DFfThTBkWY5o22odDks7sHs6+IMLQXefsfe7x/3jv/ljrd9Y+Z+21zzHkIGdtLXArMAO4FmgE6oCRvskAcATYD3wP7AJ2GpHjsW0zEZ2+ALgfeBi4HSgphxgEPgHeAN4xIv+cEwCctSOBJcBSf5VD6DfgRWCjERkoLABnbTPwEnBFpMD6GXjMiLQVCoAP95eBReSjLcDiENFgAjjfAHwATCZffQPcY0R+qRoAZ+0UoAO4nOqoD7jLiHyXOwBnbaN/XNVTXf0KzDAiB3ID4Ky9COgCrqEY6gFuMCJ/ajuWUk74WoGcB5gIvJqmYynF1X8EaKZ4muOsXRB1CThrx/hwG5Pl3gl8BfwAHPK/1fuImprxxnwEmKRJoc9TTvBkBucPAxt8Wts3DOBxPn1eAYxNMUcdsApYHjwCnLWXAAeAC5VGDQHrgXWVJi7O2lEe9hMpIuIEMN6I9IeOAJvC+QFgvhFpVa1LkRPASmftXr8Z0sw7ytvaEvom+FCKKz9P6/xZIN4FZvudoUbzgz4FnLVTgUlKI1YZkfbMubrIh8Czym6TnbXXh4yAO5UG9Prtayht8E8Nje4ICeAW5eRPG5FTwbasyVjaKJgZEsB1yrvwexESnVZ/U61UU4IAcNaOABoUE3cYkZOhvfclsY8UXa5y1p4fIgJqgRrlPj1mDUCT5NWGADBaaeShiAC0Y48OAUCbiZ2MCEBbGa4JAaBfOWnMAsllyva/hwBw3Gd1laohIgDN2EPAH5kBGJFB5dq7O4bnzlqjHPugtz1IHtCtmHi8s3Z6BAZNwJWK9hXZXCmAvUpjV0cA8JSyfVdIAJ8pJ5/lrL05YPjfBtyn7LYnJIBdwDFN4gZs9RWerM7XA28qu/UDu4MB8JuR91M8DtuctXUZnB8LbEN/8NJuRE6HLoikKWw0AV3O2mkpnG/y6zjNDbViWzUlsW0kVVftFW3wEDYDa4zIwf9xfBzwDLBQuQcp6zDJWWXFa1VzVdaTVGzTatCvze3APpJzf4BLSQ437gVuSul4WeuMyOoYEQAgJCXntCdKNb5QMZM4csAmTQeVI0bkJ6Cd4qrViOyPBqAcYgUG0KLtoAZgRLqAjwvofIcR6Y4OwOu5AgJIZVMqAEak0z8Wi6I2I7I7NwBey4HTBXB+kOQckVwBGJF9wOsFALDJiHybOwCvFcDRKjrfn3XrnQmAP4JeWUUAy4zI0aoB8NpM8k5v3vqU5Og8k0K9KToR+BoYkZPz/wLTsrwfGDICMCI9wAs5Xv3nQzgfDIDXWpL3/WPrx5DpeDAA/vByAfq3OTQaAhaF/HYgZATgs7GWiADWGpGdIQcsRTByDfB5hHG7/TILqiifzDhrrwa+RH+yPJwGgOlGpDe0rTEiAF+UWBZwyCUxnI8WAWdEwtvAnIzDbDUiD8SysURcLST5DC6teoFHYxoYFYB/43MW8HfKdd9sRP46ZwGckSXaFF0XZ9nmFgaAh/AWsFHR5RUjsiUP23IB4LUU2FFBu07g8byMMjkCKH9DvAeYMEyTHuDGPL4ZrgoAD6ER+AK4+Ky/jnnne/O0p5Q3AH+6NNvv6cs6BczN2/mqAPAQOoF5JB8+9gEPGpEd1bDlPxuGasiiOeyPAAAAAElFTkSuQmCC",
    orange: "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAABmJLR0QAAAAAAAD5Q7t/AAAACXBIWXMAAA7EAAAOxAGVKw4bAAAAB3RJTUUH5AIYDwMyRsqaWgAABPFJREFUeNrVm22IVkUUx3/PWkh5hFhL27LWNkzNCHU/RNkrBQVF4LpZQiWRCX4QcqwUrSiSVYOGKPzSK2Ufwopd0cqNItwsaxMq6MXdMiy2NGu1l9mSdNc+3FkQYek5c2fuc/1/3L0zc85vzsw9c+a5FQqQs9QDVwGzgQuBJmA8MMY/MgDsB3YD3wDbgW1iOJjatkpCp08BbgHuBK4B6pRdDALvAy8Dr4vhnxMCgLOMAZYAS/0sx9AvgAXWi2GgtACcpQV4EjgnUWD9ANwrho5SAfDh/hSwkGK0AVgcIxoqEZxvBN4GplGsvgRuFMOPNQPgLNOBTuBsaqM+4HoxfF04AGdp8q+rBmqrn4HZYthTGABnOQ3oBiZTDvUAl4jhD23DusABny+R8wBTgOdCGtYFzP7dQAvlU6uzLEi6BJxlnA+3cTkMPQp8DnwL7PV/a/ARNSPnxrwfmKpJoU9SDvBgDuf3Aet8Wts3AuCJPn1eDkwIGGM8sBK4P3oEOMsZwB7gVKVRQ8BaoK3axMVZxMN+ICAiHDBJDP2x94BFAc4PAK1iWKXJ2sTgxLDCR8PfyjHF2xp9E7w9YObni6E9dEGL4Q1grj8ZanRHVADOMgOYqjRipRg2593axbAVeETZbJqzXBwzAq5TGtDrj6+xtM6/NTS6NiaAK5SDPyyGw7G8931po+DKmAAuUu7CmxIkOu1+U61W06MAcJbRQKNi4E4xHIrtvS+JvaNocp6znBwjAuqBUcpzesoagCbJq48BYKzSyL0JAWj7HhsDgDYTO5QQgLYyPCoGgH7loCkLJGcpn/8tBoCDPqurVo0JAWj6HgJ+zw1ADIPKtXdDCs+dpaLs+ydve5Q8YKdi4EnOMisBg2bgXMXzVdlcLYBPlcauSgDgIeXz3TEBfKQcfI6zXB4x/K8GblY22xETwHbggGLwCrDRV3jyOt8AvKJs1g98GA2AP4y8FfA67HA2/ILUWSYAW9BfvGwWw5HYBZGQwkYz0O0sMwOcb/brOGRDrdpWDYAtZFXXkHd3t7M84+z/z6SzTHSWZ4FPlLv+sPaR3VVWvVY1s7KWrGIbqkG/Nt8EdpHd+wOcSXa5cRNwmfLwdbzaxFT/FtICaPKVmTrKqaPAZDHsTrEEEMP3kL/Ol1DtGucJnMm2EgNYo22gBiCGbuDdEjrfKUaVsgdHAMBjJQQQZFMQADF0+ddiWdQhprrML1YEQHYBeaQEzg+S3SNSKAAx7AJeKgGAF8TwVeEAvJYDv9bQ+f68R+9cAPwV9IoaAlgmJt8ExMjoXiT7TW/R+oDsd8S5FOuXolOAL4DRBTn/LzAzz+8DY0YAYugBnihw9h+P4Xw0AF6rQZeHB+q7mOl4NAD+8nIB+l9zaDQELIz57UDUY63PxtYkBLBaDNtidpjiXP8o8HGCfnf6ZRZVST6ZcZbzgc/Q3yyPpAFglhh6Y9uapLLjixLLIna5JIXzySLgmEh4DWjN2c1GMdyaysbUtb27yD6DC1UvcE9KA5MCEIMD5gB/Ba77FjH8ecICOCZLXBTQdHGeY25pAHgIrwLrFU2eFsOGImwrsr6/FHiviue6gPuKMqpSIIDhb4h3ABeM8EgPcGkR3wzXBICH0ER273f6cf864J3vLdKewq+4/O3SXH+mH9ZhYF7RztcEgIfQBcwn+/CxD7hNTFX7Q3T9B0t6NqrgieNTAAAAAElFTkSuQmCC",
    white: "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAQAAAAAYLlVAAAAAmJLR0QAAKqNIzIAAAAJcEhZcwAADsQAAA7EAZUrDhsAAAAHdElNRQfkAhgPBA9R40CMAAABI0lEQVRo3u1ZUQ7FIAhbjfe/8va15GWZEwqo5LnfRSgFUSoO9Xee7X+A1hq8XLMw4O1cCwIx7uUQEONcDgKR7iUQEOu+DwHR7nsQEO/+G0I5Jn8YEf8XBxjjvg2h+hjkAYOL/y0ablV1zCYYJopzW/E4jq3nvW799D5Q/Ojn0rBeJ2xnUBOZ3EquGtgA/gOAvpla9oCKgYg7QrYakHGgY6p4ZZeeIfVGQF/l31YWzxpnyrSy2+wZDbtHpl/L92S0LgN7Oh4lUKzNwAiNaHUG4mW69RmYrpSaTjqB9QwpYDlwU8vJu57QcpYUaDmQz1d53ozkELJrRFYOtNM1MYxPfLjsQWC0hXw10OaA01ZoQeYJgZV2DIrQLwReWTJJUjcEi7B1AXKEZmB2CveeAAAAAElFTkSuQmCC",
    yellow: "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAABmJLR0QAAAAAAAD5Q7t/AAAACXBIWXMAAA7EAAAOxAGVKw4bAAAAB3RJTUUH5AIYDwIuS9D3VAAABRZJREFUeNrlm12IlkUUx3/v0RBzhdht1E1LWzF3NcwP+tLSwiKhiFyM7vIiEbwQCqlEK4Ji1aCIwpu+oLyJCjS0TClCy6JtoSJrdcuwstycNvvYLdvas128R1gWlt55npn3fbID783uMzPn/5//zJw5M1OiCqbq6oElwCJgFtAETADG2Sd9wAngCNAJvAvsE/EnU/tWSgh6LHArcDtwLSCBVQwAbwMvAK+I+D/+EwSounHAWuAu6+UY9gPwGLBVxPcVlgBV1wo8DpyfSFhfA3eK+B2FIsDk/gSwiurYNmBNDDWUIoCfCuwGWqiuHQRuFPHf1IwAVTcb2ANMpjZ2DLhBxH9edQJUXZMtV43U1r4HFon4o1UjQNWdA7QDMyiGHQYuF/G/hBaUjA0+WyDwADOBZ7IUlAy9fwfQSvFshapbmXQIqLoGk1tDDkcHgY+BL4Dj9rdGU9TcnBPzCaA5JIQeHdjAfTnAdwNbLKw9NgLBUyx8vheYmKGNCcAG4O7oClB1DjgKnB06aoDNQFulgYuqqzOy78mgiF5gmojviT0HrM4Avg9YIeI3hkRtIr5XxK83Nfwe2Gad+RpdAZ1Ac2DP3yLid+YMtpYBu4BRAcU6RfysaApQdXMDwQNsyAve1PAG8GBgsRZVNyfmELgu0IEu277Gsi22aoTY0pgEXB3Y+AMi/q9Y6K2uUBUsjknAxYGz8KsJAp3tNqlWarOjEKDqxgBTAxreI+JPxUZvKbG9AUUuVHVnxVBAfeAMfDBxDiAkyKuPQcD4QCePJyQgtO7xMQgIjcROJSQgNDM8KgYBPYGNpkyQnBf4/Y8xCDhpUV2lNjUhASF1K/BzbgJE/EDg2FuWArmqKwXW/Z35HiUO6AhoeJqqm5+AgwXABQHfV+RzpQR8GOjsxgQE3B/4fXtMAt4LbHy5qrsqovyvAW4OLPZ+tO2wRVTdlQQWw9bsy0bK/gSAbzQFhpw99ACTRPzfURRgm5HXMyyHO1TdhBzgJ1ouIPTgZWcl4EOGwOnNSJaJq13VzcsAfoGN4ywTasW+hhCwi3LWNcva3a7qnlJ1kysAPkXVPQ18EDjrn7ZuymeVRJsDhji3mXLGNqsNAAeA14BDlM/9ASZRPty4CVgYuPkabm0ifmMqAposMyMU0waBGSL+SIohgIj/CthJcW17CHgy9mRbgQnYFJxoyZCZaQfeLCD4PSK+IzkBZg8VkIBMPmUiQMTvt2WxKLZDxB/IUjDPDZFm4FPCD1hj2wBwiYj/rGoKMBUcAp4vQO8/lxV8LgWYChooX211NQLfA7SIeJ+5I/O0bkfQ62vY++vygM+tAFNBCXiL8n3gato7wBIRP1hTAoyEmcAnwJgqge8H5uW5HxhlCAwZCoeBR6vY+4/EAB9NAaaCsbYsTk8M/ktgTqzr89F2debQSluXU5kCq2K+HYi6rbVobFNCAh4W8ftiVpjiwcRom6GviFx1B7Aw5sWLJAQYCdOBjwg/WR7J+oD5Ir4rtq9JMjuWlFgXscq1KcAnU8AQJbwMrMhZzUsi/rZUPqYmoI5yajvra5Iu4FIR/2sqH5MmN0V8L7Ac+C3juG9NCT45AUOixNUZiq7Js80tDAFGwovA1oAiT4r4bdXwrUSVzA5Yd/PvNzj3A9eL+P4zigAjoZ7ysfVFI3xyGLiyGm+Ga0KAkdBE+dzv3GH/+snAd3Gmm6pbrOr+VHWD9utXdUv5P5mqa1V139qvZo+w/gFDtZdfQgQIQgAAAABJRU5ErkJggg==",
    green: "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAABmJLR0QAAAAAAAD5Q7t/AAAACXBIWXMAAA7EAAAOxAGVKw4bAAAAB3RJTUUH5AIYDwAZwVsw2QAABRFJREFUeNrVm22IVUUYx3/3biGlQqy1tmWtbZSaEXqWIcqyoqCgCFw9lZCJZIIfhMRM0d4kcTUoovBLlFL2IZxiN9ZeNpJw06ydZSroxd0yLNY0bbUXlyTdtQ9nFkRYus85M+ce/x/vnZfn+Z1nzpl5ZqZEDopNVAvcAswArgEagTpgtCsyABwC9gLfAzuBHVrZo6FtKwV0+jwgBh4CbgPKwiYGgU+AN4C3tbL/nBUAYhONBpYAS91T9qHfgBeAjVrZgcICiE3UDLwIXBYosH4GHtXKthUKgAv3l4CF5KMtwGIf0VDy4HwD8AEwhXz1DXC3VvaXqgGITTQV6AAupTrqA+7Uyn6XO4DYRI3uc1VPdfUrMEMruy83ALGJLgC6gKsohnqA67Wyf0orllN2+FqBnAeYBLyapmI5xdN/GGimeJoTm2h+0CEQm2icC7dxGQw9BXwF/AAccL/Vu4ialvHFfAiYLJlCnyPs4IkMzh8ENrhpbd8IgCe46fMKYHyKPuqAVcBy7xEQm+giYB9wvtCoIWA9sK7SiUtsojEO9uMpIuIYMFEr2+87AhalcH4AmKeVbZVU0soeA1bGJjJuMSTpd4yztcX3S/DBFE9+rtT5M0C8A8x2K0OJ5nn9CsQmmgZMFhqxSivbnvXVrpX9EHhGWG1KbKLrfEbAHUIDet3y1Zc2uK+GRLf7BHCzsPOntLInfHnv2pJGwUyfAK4VvoXfDTDRaXUv1Uo11QuA2ESjgAZBxx1a2eO+vXcpsY8EVa6ITXSujwioBWqE6/SQOQDJJK/WB4CxQiMPBAQgbXusDwDSmdjxgACkmeEaHwD6hZ2GTJBcIiz/uw8AR92srlI1BAQgaXsI+CMzAK3soHDs3RXC89hEJWHb+53tXuYB3YKOJ8YmigIwaAIuF5SvyOZKARihsasDAHhSWL7LJ4DPhJ3Pik10k8fwvxW4V1htt08AO4Ejgs5LwFaX4cnqfD3wprBaP7DLGwC3GHk/xeewLTZRXQbnxwPbkG+8tGtlT/pOiKRJbDQBXbGJpqdwvsmN4zQv1IptlaTEtpFkXaVPtMFB2Ays0cru/x/HJwBPAwuEa5BhHSTZq6x4rEqeynqSjG1aDbqx+R6wh2TfH+Biks2Ne4AbUzo+rHVa2dUhIgDgFZKUc9odpRqXqJhJGJ0CNkkqiBzRyv4EtFNctWpl9wYDMBxiBQbQIq0gBqCV7QI+LqDzHVrZ7uAAnJ4tIIBUNqUCoJXtdJ/FoqhNK7srNwBOy4GTBXB+kGQfkVwBaGX3AK8XAMAmrey3uQNwWgEcrqLz/VmX3pkAuC3olVUEsEwre7hqAJw2k5zpzVufkmydZ5Kvk6KTgK+BUTk5/y8wPcv5QJ8RgFa2B3g+x6f/nA/nvQFwWkty3j+0fvQ5HfcGwG1ezkd+mkOiIWChz7sDPiMANxtrCQhgrVZ2h88GywGMXAN8HqDdbjfMvCrIlZnYRFcCXyLfWR5JA0Ckle31bWuICMAlJZZ5bHJJCOeDRcBpkaCBORmb2aqVvT+UjWXCagHJNbi06gUeCWlgUADuxOcs4O+U475ZK/vXWQvgtFniohRVF2dZ5hYGgIPwFrBRUOVlreyWPGzLBYDTUmB7BeU6gcfyMqqUI4DhO8S7gatHKNID3JDHneGqAHAQGoEvgAvP+OuIc743T3vKeQNwu0uz3Zp+WCeA+/J2vioAHIROYC7Jxcc+4AGt7PZq2PIfiaJ2INYnNtcAAAAASUVORK5CYII=",
    red: "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAABmJLR0QAAAAAAAD5Q7t/AAAACXBIWXMAAA7EAAAOxAGVKw4bAAAAB3RJTUUH5AIYDjoss4NAtAAABNVJREFUeNrd22molkUUB/DfvRphKYSmZVmaYmqGpA5U2kpBQRG4VASVRCb4QUhsQyuCwiUoovBLKy0fwgoNbTGK0CzJHqho1RZaLM262qIlufXhGUEE4Z3nnee9r/3hfrnvMzPn/OfMzJlzznRoAQr64nxMxGkYigE4On6yA1vwDb7AGqwKbKtbto4ale6FK3E9LkRnYhd78DaewYuBfw4LAopyVmdhdpzlHPgFD2JxKK2lPQkomIyHcFJNhvU9bg4saysCork/jOlag2cxM4c1dGRQfjBewyitxae4LPBDtxFQMBorcaLuwUZcEvi85QQU5VG2BgN1L37GxMB3LSOg4Bisw3DtgfU4M/BHasPOigM+0UbKwwg8XqVhZ4XZv1F53LUbphZMq3UJFPSL5tavCUH34SN8hU3xfwOjRZ3R5Ma8BSNTXOieiQPc2YTym7EourUbD0HwoOg+347jKowxAHNxa3YLKOiv3GmPShRqLxZifqOOS0HvSPZtFSxiO4YEunLvATMqKL8DUwPzUry2wPbAHdEa/k4cs3eUNfsmeG2Fmb8msLTqgg68hCnxZpiC67ISUJSb08hEIeYGlje7tQdexz2JzUYVjMlpARcnCrAhXl9zYVE8NVJwUU4Czk0c/O7Arlzax75SreC8nAScnrgLv1yDo7NU2vV3dBYCCo5UXnkbxcrAztzax5DYGwlNTik4IocF9EWPxHt6nTGAFCevbw4C+iQKualGAlL77pODgFRPbGeNBKRGhnvkIKArcdA6AyQnJH7/Ww4CtkWvrlEMrpGAlL734vemCQilG5qy9i6tQ/OiXIopff8UGnChOxsfv2EMKRhXAwfjcXIaZ/kcoQ8ShZ1XAwF3JX6/LicB7yUOPqngnIzmfwGuSGy2NicBa7A1YfAOLIkRnmaVH4jnEpt14d1sBMTLyKsVjsNlRRMJ0qIMi62QnnhZHtidOyBSJbAxHusKxlZQfnxcx1U21IZlTSFghTLqWuXsXlfwaNHATBYMKngM7yfu+vuxWZmrbHitpszKQmXEtir2xLX5Cr5U5v3heGVy43JMSLx8HYz5IeEUSiVgaIzMdGpP7MPwUJbaZF8CAt/KEOerEUtTlFdxJue3MQELUhskExDKnfnNNlR+ZUhz2StbANzbhgRUkqkSAYHV8VhsFywLDXp+uSyAMgG5uw2U36PMI2opAaE8x59uAwKeDHxWtXGzRVL9lKWt/btJ+S6MCvzacguIVtClzOJ2F+Y0o3zTBEQ8pazpbTXeUdYRN4VclaIj8LEyi9QK/IuxzdQH5rQAoawbeqCFs39/DuWzWUC0gl74BMNqVv5rjMlVPp/tVhcFmia9miMFezE959uBrNfa6I0tqJGA+wKrcnZYx4OJnnGHPit/1ybkLLyohYAo6TB8KD2zfCjswLhQlt5kRS2RnRiUmJOxy1l1KF+bBRxgCS9gapPdLAlcXZeMdcf2boh3harYgJvqFLBWAkJZMDUJf1Vc95MDfx62BBzgJc6o0HRmM9fctiEgkvA8Fic0eSSUL8P8LwiImI23GvhuNW5plVAdLSRg/xvitTj1EJ+sx9mteDPcLQREEoYq837HHvTT1qj8hlbK0/IUV8wuTYl3+v3YhatarXy3omBywY/xr9seYf0HXNIMyfp4RR8AAAAASUVORK5CYII=",
    blue: "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAABmJLR0QAAAAAAAD5Q7t/AAAACXBIWXMAAA7EAAAOxAGVKw4bAAAAB3RJTUUH5AIYDjsaZSLkbAAABORJREFUeNrVm22IVkUUx3/PWkipEGutbVprG6bmEOp+iLJXCgqKwJ3tRagkMsEPQmKmuBVFsmpQROGXXin7ENawG6vVRhJumvW0UMFU7pahsqVpq73slqS79mFGBGHhOXNn7nP9f3yeOzPn/O6ZuWfO3FsiD2lbC9wAzAOuABqBOmCcv2IIOAjsBn4AtgPbMOpIatNKCZ0+B7gLeAC4CagR9jAMfAq8BbyHUf+eGQC0HQcsBZb5uxxDvwHPAxswaqi4ALRtBl4ALk4UV3uBRzCqo1gAXLi/CCwiH20ElsSIhlIE5xuAD4GZ5CsL3I5R+6oHQNtZQBcwmeqoH7gVo77PH4C2jf5xVU919SswD6P25AdA2/OAMjCNYqgXuAqj/pQ2rAkc8LUCOQ8wHXg1pGFNwN1/CGimeGpB24Vpp4C2E324Tcxg6AngG+BHYL//rd5H1OyMC/NBYIYkhT5LOMDjGZw/AKz3aW3/KICn+PR5JTApYIw6YDWwIn4EaHsBsAc4V2jUCLAOaKs4cdF2vIf9WEBEDAJTMWog9hqwOMD5IaAFo1pFWZtRgxi1ykfDP8Ixx3tboy+C9wXc+QUY1R48o40ygPY7Q4nujwtA29nADKERqzGqM/PabtRHwFPCVjPR9sqYEXCL0IA+v32NpfX+qSHRzTEBXCcc/EmMOhbNfdeXNAqujwlACVfh9xMkOu1+Ua1Us+IA0HYs0CAYuAujjkZ335XEPha0uBRtz44RAbXAGOE+PWUNQJLk1cYAMEFo5P6EAKR9T4gBQJqJHU0IQFoZHhMDwIBw0JQFkouE1/8eA8ARn9VVqoaEACR9jwB/ZAdg1LBw7t2WxHVtS8K+f/G2R8kDegQDT0XbuQkQNAGXCK6vyOZKAXwlNLY1AYAnhNeXYwL4XDj4fLS9NmL43wjcKWy1MyaA7cBhweAlYJOv8GR1vh54W9hqANgRD4DbjHwQ8DjsQNu6DM5PAjYjP3jpxKjjsQsiIYWNJqCMtnMCnG/y8zhkQa3YVgmAzbiqa8izu4y2L6Pt5Aocn4K2rwBfClf9kzqAO6useK5K7so6XMU2VMN+bm4BduHO/QEuxB1u3AFcI9x8na42jGpNBaDRV2ZqKKZOANMwaneKKQBG/Qx0Uly1S5wn8E62FRjAWmkDOQCjysAnBXS+C6N60gNweqaAAIJsCgNgVLd/LBZFHRi1Iz8ATiuA4wVwfhh3jki+AIzaBbxZAACvY9R3+QNwWgkcqqLzA1m33tkAuCPoVVUEsByjDlUPgNMbuHd689ZnuPeIMynWm6LTgW+BsTk5/x8wJ8v7gTEjAIzqBZ7L8e4/G8P5eACc1uDe90+tn2Km4/EAuMPLhcjf5pBoBFgU89uBuNtal42tTQhgDUZti9lhin3908AXCfrt8dMsqtJ8MqPtZcDXyE+WR9MQMBej+mKbmqay44oSyyP2uDSF8+ki4FQkvAu0ZOxlE0bdk8rE1LW9B3GfwYWqD3g4pYFpARg1CMwH/g6c980Y9deZC+BUlrg4oOWSLNvc4gBwEN4BNghavIRRG/MwLc/6/jJgawXXdQOP5mVUiTzlviHeCVw+yhW9wNV5fDNcHQAOQiPu3O/80/457J3vy9Oc/I+43OmS9nv6kzoG3J2389UB4CB0AwtwHz72A/di1NZqmPI/FK4/MlP45KgAAAAASUVORK5CYII="
};

var tourism = [
    {
        text: 'Tourism',
        color: 'pink'
    },
    {
        text: 'Accommodation',
        color: 'orange'
    },
    {
        text: 'Culture',
        color: 'purple'
    },
    {
        text: '',
        color: 'purple'
    },
    {
        text: 'Information',
        color: 'yellow'
    },
];

class UIMap {
    constructor(cpp_ui_map, ll_map) {
        this.cpp_ui_map = cpp_ui_map;
        this.map = ll_map;

        this.map.l_map.on("click", this.onMapClick);
    }

    onMapClick(e) {
        let map = window.map;
        let ui_map = window.ui_map;

        let latlng = e.latlng.lat.toFixed(6).toString() + "," + e.latlng.lng.toFixed(6).toString();

        let start = "<button onclick='ui_map.setStart(\"" + latlng + "\")'>Set start</button>";
        let stop = "<button onclick='ui_map.setStop(\"" + latlng + "\")'>Set stop</button>";

        map.l_popup.setLatLng(e.latlng)
            .setContent(start + "&nbsp;" + stop)
            .addTo(map.l_map);
    }

    // JS -> C++

    onLoad() {
        this.cpp_ui_map.onLoad();
    }

    // setMapBounds() {
    //     let bounds = this.map.l_map.getBounds();
    //     let sw = bounds["_southWest"];
    //     let ne = bounds["_northEast"];
    //
    //     this.ui_bridge.setMapBounds(ne.lat, ne.lng, sw.lat, sw.lng);
    // }

    setStart(latlon) {
        this.cpp_ui_map.setStart(latlon);
        this.map.routeLayer.clearLayers();
        this.map.l_map.removeLayer(this.map.l_popup);

        latlon = latlon.split(",");
        this.map.l_start.setLatLng(latlon).addTo(this.map.l_map);
    }

    setStop(latlon) {
        this.cpp_ui_map.setStop(latlon);
        this.map.routeLayer.clearLayers();
        this.map.l_map.removeLayer(this.map.l_popup);

        latlon = latlon.split(",");
        this.map.l_stop.setLatLng(latlon).addTo(this.map.l_map);
    }

    addAttraction(id) {
        this.cpp_ui_map.addAttraction(id);
    }

    // C++ -> JS

    setView(lat, lon, zoom) {
        this.map.setView(lat, lon, zoom);
    }

    showGraph(bool) {
        this.map.showGraph(bool);
    }

    showRoute(clear, route=[], color=0) {
        this.map.showRoute(clear, route, color);
    }

    showNodes(show, nodes) {
        this.map.showNodes(show, nodes);
    }

    resetAttractions() {
        this.map.resetAttractions();
    }

    addAttractions(n) {
        this.map.addAttractions(n);
    }

    removeAttractions(n) {
        this.map.removeAttractions(n);
    }
}

class UIGraph {
    constructor(cpp_ui_graph, map) {
        this.cpp_ui_graph = cpp_ui_graph;
        this.map = map;
        this.l_renderer = L.canvas({padding: 0.5});

        this.graphs = {"motorway": []};
        this.layers = {"motorway": L.layerGroup([])};
    }

    computeGraph(type) {
        this.graphs["motorway"] = JSON.parse(this.cpp_ui_graph.motorway);
    }

    show() {
        let zoom = this.map.l_map.getZoom();

        if (zoom > 15) {
            L.polyline(this.graphs["motorway"], {
                renderer: this.l_renderer,
                color: style['edgeColor'],
                interactive: false
            }).addTo(this.map.l_map);
        } else if (zoom <= 15 && zoom > 12) {
            // primary
        } else if (zoom <= 12 && zoom > 10) {
            // secondary
        }
    }
}

function newIcon(type) {
    return L.icon({
        iconUrl: icons[type],
        opacity: 0.5,
        iconSize: [32, 32],
        iconAnchor: [16, 32],
        popupAnchor: [16, -32],
        type: type
    });
}

class Map {
    constructor() {
        this.l_map = L.map('map').setView([0, 0], 10);

        this.attractions = [];
        this.markers = {};
        this.l_popup = L.popup();
        this.l_start = L.marker([0, 0], {
            icon: newIcon('blue'),
            riseOnHover: true,
            riseOffset: 10
        }).bindPopup("Start");

        this.l_stop = L.marker([0, 0], {
            icon: newIcon('red'),
            riseOnHover: true,
            riseOffset: 10
        }).bindPopup("Stop");

        this.routeLayer = L.layerGroup([]);
        this.nodeLayer = L.layerGroup([]);
        this.graphLayer = L.layerGroup([]);

        this.showNetwork = false;

        let token = 'pk.eyJ1IjoibWFwYm94IiwiYSI6ImNpejY4NXVycTA2emYycXBndHRqcmZ3N3gifQ.rJcFIG214AriISLbB6B5aw';
        L.tileLayer('https://api.tiles.mapbox.com/v4/{id}/{z}/{x}/{y}.png?access_token={token}', {
            maxZoom: 20,
            attribution: '',
            id: 'mapbox.streets',
            token: token
        }).addTo(this.l_map);

        this.nodeLayer.addTo(this.l_map);
        L.control.scale().addTo(this.l_map);
    }

    setView(lat, lon, zoom = -1) {
        let _zoom = zoom === -1 ? this.l_map.getZoom() : zoom;

        this.l_map.setView([lat, lon], _zoom);
    }

    showGraph(show) {
        this.showNetwork = show;

        if (!this.showNetwork) {
            this.l_map.removeLayer(this.graphLayer);
        } else {
            this.graphLayer.addTo(this.l_map);
        }
    }

    showRoute(clear, lines, color) {
        this.routeLayer.clearLayers();

        if(clear)
        {
            this.routeLayer.addLayer(L.geoJSON({
                type: "LineString",
                coordinates: lines
            }, {
                style: {
                    color: color ? colors[color] : style['routeColor'],
                    weight: 4
                }
            })).addTo(this.l_map);
        }
    }

    showNodes(show, nodes) {
        this.nodeLayer.clearLayers();

        let button = function (obj, text, id, marker) {
            let button = document.createElement('button');
            button.innerHTML = 'Add to route';
            button.onclick = function () {
                if(obj.attractions.indexOf(marker) === -1)
                {
                    ui_map.addAttraction(id);
                    if (obj.attractions.length === 10) {
                        let change_marker = obj.attractions.pop();
                        change_marker.setIcon(newIcon(change_marker.type));
                    }

                    marker.setIcon(newIcon('green'));
                    obj.attractions.push(marker);
                }
            };
            let p = document.createElement('p');
            p.innerHTML = text;
            p.appendChild(document.createElement('br'));
            p.appendChild(button);
            return p;
        };

        if (show) {
            for (let i = 0; i < nodes.length; i++) {
                let n = nodes[i];
                let t = tourism[n[0]];
                let marker = L.marker([n[1], n[2]], {icon: newIcon(t.color)});
                marker.type = t.color;
                marker.bindPopup(button(this, t.text, n[3], marker)).addTo(this.nodeLayer);
                this.markers[n[3]] = marker;
            }
        }
    }

    resetAttractions() {
        for (let key in this.attractions) {
            let a = this.attractions[key];
            a.setIcon(newIcon(a.type));
        }
        this.attractions = [];
    }

    addAttractions(n) {
        console.log("add " + n);
    }

    removeAttractions(n) {
        console.log("rem " + n);
        while(n > 0) {
            let change_marker = this.attractions.pop();
            change_marker.setIcon(newIcon(change_marker.type));
            n--;
        }
    }
}

document.addEventListener("DOMContentLoaded", function () {

    new QWebChannel(qt.webChannelTransport, function (channel) {
        window.map = new Map();

        window.ui_graph = new UIGraph(channel.objects.UIGraph, map);
        window.ui_map = new UIMap(channel.objects.UIMap, map);

        window.ui_map.onLoad();
    });
});
