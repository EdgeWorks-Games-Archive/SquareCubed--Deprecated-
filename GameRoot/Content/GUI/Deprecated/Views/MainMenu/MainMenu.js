$(function() {
    // Main Menu Window

    $("#mainmenu-dialog").dialog({
        width: 350,
        minHeight: 0,
        hide: {
            effect: "fadeOut",
            duration: 300
        },
        buttons: {
            "Connect": function() {
                // Disable Buttons and Set Text
                $("#mainmenu-connect-progress").text("Connecting to " + server.value + "...");
                $(".mainmenu-buttons").button("option", "disabled", true);

                // Connect Animation
                $("#mainmenu-connect-input").slideUp(300, function() {
                    $("#mainmenu-connect-progress").slideDown(300, function () {
                        // Connect Engine Call
                        engine.call('Connect', server.value);
                    });
                });

            },
            "Quit": function() {
                $("#mainmenu-dialog").dialog("close");
                $(this).parent().promise().done(function () {
                    engine.call('Quit', 'User pressed Quit in Main Menu!');
                });
            }
        },
    });
    
    $("#mainmenu-dialog").closest(".ui-dialog").find("button").addClass("mainmenu-buttons");

    engine.on('ConnectFail', function() {
        // Set Status Text
        var statusText = document.createElement("p");
        $(statusText).addClass("red").text("Failed to connect to server!");
        $("#mainmenu-status").html(statusText);

        // Connect Failed Animation
        $("#mainmenu-connect-progress").slideUp(300, function () {
            $("#mainmenu-connect-input").slideDown(300);
        });

        // Re-enable Buttons
        $(".mainmenu-buttons").button("option", "disabled", false);
    });


    // Run Server Button
    $("#runserver-button").click(function() {
        engine.call('RunServer');
    });
});