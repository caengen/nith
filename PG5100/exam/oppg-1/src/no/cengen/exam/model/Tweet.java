package no.cengen.exam.model;

import java.io.Serializable;

/**
 * User: Cengen
 * Date: 02/12/13
 * Time: 13:46
 */
public class Tweet implements Serializable {
    private String tag;
    private String sender;
    private String message;

    public Tweet(String sender, String tag, String message) {
        this.sender = sender;
        this.tag = tag;
        this.message = message;
    }

    public String getTag() {
        return tag;
    }

    public void setTag(String tag) {
        this.tag = tag;
    }

    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        this.message = message;
    }

    @Override
    public String toString() {
        return sender + ": #" + tag + " " + message;
    }
}
