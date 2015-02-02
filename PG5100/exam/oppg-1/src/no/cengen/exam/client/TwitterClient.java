package no.cengen.exam.client;

import no.cengen.exam.model.Tweet;
import no.cengen.exam.server.TwitterServerIF;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.Scanner;

/**
 * User: Cengen
 * Date: 02/12/13
 * Time: 13:02
 */
public class TwitterClient extends UnicastRemoteObject implements TwitterClientIF, Runnable {
    private TwitterServerIF twitterServer;
    private String nick = null;

    private ArrayList<String> subscriptions;


    protected TwitterClient(String nick, TwitterServerIF twitterServer) throws RemoteException {
        this.nick = nick;
        this.twitterServer = twitterServer;
        subscriptions = new ArrayList<String>();

        twitterServer.registerTwitterClient(this);
    }

    @Override
    public void receiveTweet(Tweet tweet) throws RemoteException {
        System.out.println(tweet);
    }

    @Override
    public void run() {
        Scanner scanner = new Scanner(System.in);
        String subscription, tag, message;
        Tweet tweet;

        //Set subscriptions
        while (true) {
            System.out.print("Type a tag to subscribe to or type \"stop\": ");
            subscription = scanner.next();

            if (subscription.toLowerCase().equals("stop")) break;

            subscriptions.add(subscription);
            System.out.println("Tag added to subscriptions");
        }

        //Send tweets
        while(true) {
            System.out.println("\nTo tweet, write a <TAG> <TWEET>");
            System.out.println("Alternatively write \"quit\".");
            System.out.print("Tweet: ");

            tag = scanner.next();

            if (!tag.toLowerCase().equals("quit")) {
                message = "";
                message += scanner.nextLine();


                tweet = new Tweet(this.nick, tag, message);

                try {
                    twitterServer.broadcastTweet(tweet);
                } catch (RemoteException e) {
                    e.printStackTrace();
                }
            } else {
                try {
                    twitterServer.removeTwitterClient(this);
                    System.out.println("Removed from server. Have a nice day!");
                    break;
                } catch (RemoteException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public ArrayList<String> getSubscriptions() throws RemoteException {
        return subscriptions;
    }
}
