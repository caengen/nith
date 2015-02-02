package no.cengen.exam.server;

import no.cengen.exam.client.TwitterClientIF;
import no.cengen.exam.model.Tweet;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;

/**
 * User: Cengen
 * Date: 02/12/13
 * Time: 13:03
 */
public class TwitterServer extends UnicastRemoteObject implements TwitterServerIF {

    private ArrayList<TwitterClientIF> twitterClients;

    protected TwitterServer() throws RemoteException {
        twitterClients = new ArrayList<TwitterClientIF>();
    }

    @Override
    public synchronized void registerTwitterClient(TwitterClientIF twitterClient) throws RemoteException {
        this.twitterClients.add(twitterClient);
    }

    @Override
    public synchronized void broadcastTweet(Tweet tweet) throws RemoteException {
        System.out.println("Iterating through users...");
        for (TwitterClientIF twitterClient : twitterClients) {
            if (twitterClient.getSubscriptions().contains(tweet.getTag())) {
                System.out.println("Sending message to a user");
                    twitterClient.receiveTweet(tweet);
            } else {
                System.out.println("A user does not subscribe to content...");
            }
        }
    }

    @Override
    public void removeTwitterClient(TwitterClientIF twitterClient) throws RemoteException {
        twitterClients.remove(twitterClient);
    }
}
